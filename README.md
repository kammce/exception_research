# exception_v_result

Exists to test exceptions and result types and compare their impact on ROM and
RAM as well as Happy/Sad path performance.

## ⚖️ Factors that contribute to code size

### Error transport mechanism

#### ✅ Exception

Exceptions utilize an algorithm along with some slight code instrumentation in
order to manage the task of bringing an error object up to a catch statement,
and running all necessary destructors on its way up to the catch. The cost for
the unwinding mechanism is a fixed cost. As a project gets larger, the
percentage of the mechanism relative to the overall project gets smaller.

We've been capable of getting the total cost of the error transport mechanism,
in GCC, down to 5005 bytes.

#### ❌ `Result<T,E>`

Result return types require each call site to be responsible for either handling
the error or helping to transport it up a level, deferring it to a higher
function with more context to deal with it. This error handling mechanism has
no initial up front cost and thus looks cheap to use. Note that, in most cases
most functions do not have the context to determine how an error should be
handled so they typically hoist it up rather than handle it directly. As an
example, if a fixed point math operation overflows and an error is generated,
it is unlikely (or not acceptable) that the library developer of the math
library will decide to terminate or handle this error for you. That would give
less control to the application developer. Thus, the cost of each call to a
function that returns a result type requires the following:

1. Cost of the stack memory to hold the result
2. An additional instruction to pass the address of that stack memory location
   to the function.
3. The instructions to check if the result type is an error not
4. The instructions to copy/construct the error object
5. The instructions to return that error object up one function call

This will cost very little initial, but the more you make this pervasive
throughout the code base, the more the costs add up, until you finally reach
beyond 5005 bytes worth of memory. In which case exceptions become the cheaper
alternative.

#### ❓ Caveats

If the device you are working with has very little flash, below 16kB, then
result return types can be a decent alternative. Although, in such situations
where error handling will be sparse, it may also be a good idea to simply save
error information to a region of RAM that will persist and terminate/reset the
controller.

### Number of types thrown/unexpected

#### ❌ Exceptions

Each thrown type gets its own type info object created. The type info contains a
string of their type name which is inaccessible to programs with programs using
`-fno-rtti`. Each type info object occupy's a place in the `.rodata` region of
the binary. The address of that type info object is compared to the address of
the type info object in the catch statement. Note that the name of the type is
not used for comparisons as that would be too slow. The longer the type's name,
the larger that type info is. This cost is only paid once, so the same object
can be thrown multiple times without generating additional type info objects.

**How to fix this for exceptions?** Patch GCC to add support for
`-fno-exception-type-names`, which would strip out type info type names when
`-fno-rtti` and `-fexceptions` are both being used. This way, we save a bit more
memory when using exceptions and no longer have to be concerned with the length
and number of exceptions through. IMHO a 32-bit word for each thrown value is a
very cheap price.

#### 🟡 `Result<T,E>`

The number of error types does not directly affect the binary size. But there
is a limitation where, if the error type is NOT the same across all functions
in a call stack, then when a function of return type `Result<T, E1>` calls a
function of return type `Result<T, E2>`, then the first function either needs
to handle the error within its scope, which it may not have enough context to do
so, or it must transform `E2` to `E1` which may result in information loss. An
extreme example is return `std::expected<int, my_error_t>` to a function that
return `std::optional<int>`. The info in `my_error_t` will be destroyed.

### Number of functions using classes with non-trivial destructors

Both systems have to pay a cost for handling non-trivial destructors. There is
no way around this.

#### ✅ Exception

Exceptions utilize a region of the function where the non-trivial destructors
can be called in reverse order of their creation. It will look something like
this:

```arm
6e2e: e008       b.n 6e42 <funct_group13_18()+0x56>
6e30: a801       add r0, sp, #4
6e32: f7f9 fa45  bl 2c0 <class_1::~class_1()>
6e36: 4668       mov r0, sp
6e38: f7f9 fa1a  bl 270 <class_0::~class_0()>
6e3c: f000 fbce  bl 75dc <__cxa_end_cleanup>
6e40: e7f9       b.n 6e36 <funct_group13_18()+0x4a>
6e42: a801       add r0, sp, #4
```

In address `6e2e` you can see the instruction `b.n 6e42` which means,
unconditional branch to location `6e42`. Its jumping over the region that
destructs the classes with non-trivial destructors. When the exception unwind
mechanism is running, it will find this location in the list of functions with
cleanup work and will either place the program counter at `6e30` which will
destruct both classes or will place it at `6e36` to destruct only `class_0`.
The function `__cxa_end_cleanup` simply runs the `unwind_resume()` function
from `libunwind` to continue up the stack until a catch is reached.

#### ❌ `Result<T,E>`

Result types on the other hand, require additional branching to support running
the destructors and returning the error value. Below we see a factory function
that returns `tl::expected<class_0, my_error_t>`. If the result of the factory
function is not a error, then it branches over the else handler and continues
running. If the result was an error, then the else branch is taken and it has
to manage constructing the result object and destructing the original object.

```arm
ad2e: a802       add r0, sp, #8
ad30: f7f5 fa40  bl 1b4 <class_0::make(long)>
ad34: f89d 300c  ldrb.w r3, [sp, #12]
ad38: b94b       cbnz r3, ad4e <funct_group13_18()+0x32>
ad3a: 9a02       ldr r2, [sp, #8]
ad3c: 9206       str r2, [sp, #24]
ad3e: 6022       str r2, [r4, #0]
ad40: 7123       strb r3, [r4, #4]
ad42: a802       add r0, sp, #8
ad44: f7f5 fa82  bl 24c <tl::detail::expected_storage_base<class_0, my_error_t, false, true>::~expected_storage_base()>
ad48: 4620       mov r0, r4
ad4a: b009       add sp, #36 ; 0x24
ad4c: bd30       pop {r4, r5, pc}
ad4e: 9902       ldr r1, [sp, #8]
```

⚖️ Comparing the two:

Exceptions are not burdened with the task of transporting errors to their
destination. This responsibility is placed on the exception runtime algorithms
that can be reused for every possible function in the entire application.
With result types, each function that participates in error transport must also
do the work of transporting errors.

### Cost of error handling routine

#### ❓ Exceptions

The cost of handling an error with a try/catch is:

```
TBD (need to investigate this...)
```

#### ✅ `Result<T,E>`

Since the machinery for handling errors is always local, the moment a handler
gets a response from a function, it can choose to handle it or transport it up.
This means that the error can be handled at any point in the stack. The overall
cost of handling an exception is no greater than the cost of an if/else
statement.

Because we assume that handlers are rare in software, the overall cost for
handling a routine with result types is smaller.

## 🏎️ Factors that contribute to sad path performance

### Reaching the error handler

[INCOMPLETE]

#### 🟡 Exceptions when they work well

Additional information:
exceptions work in two phases in GCC, the search phase and unwind phase.
The search phase traverses up the call stack quickly to find the appropriate
catch statement. If it does not find one, it executes terminate. This allows
the program to terminate quickly when no viable handlers are available. If it
does find a suitable handler, it begins phase 2. Phase 2 is where the exception
mechanism follows the stack link registers like a linked list, figures out which
functions have destructors to execute, executes them if they are required, and
resumes stack traversal until it reaches the designated catch blocks. The list
of functions with non-trivial destructors with possible throwing behavior is
organized in a sorted list of functions based on their addresses. Given the
current

#### 🟡 `Result<T,E>`

## 🏎️ Factors that contribute to happy path performance

## Limitations

## Benefits of



## :busts_in_silhouette: Contributing

See [`CONTRIBUTING.md`](CONTRIBUTING.md) for details.

## License

Apache 2.0; see [`LICENSE`](LICENSE) for details.

## Disclaimer

This project is not an official Google project. It is not supported by
Google and Google specifically disclaims all warranties as to its quality,
merchantability, or fitness for a particular purpose.
