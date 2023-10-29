# exception_v_result

Exists to test exceptions and result types and compare their impact on ROM and
RAM as well as Happy/Sad path performance.

## How to run Performance benchmarks

To generate the code & compile it:

```bash
python3 generate.py > info.csv
conan build . -pr baremetal.profile
```

The info.csv has information about each group ID and what its call depth is
and its percentage of functions with clean up routines.

Open a new terminal and run the following, replace the `target` with your own:

```bash
pyocd gdbserver --target=lpc4088 --persist
```

You'll need a JTAG or SWD debug probe connected to your host machine as well as
have that debug probe connected to your target device.

In the same terminal you compiled the code run:

```bash
source build/MinSizeRel/generators/conanbuild.sh
```

This will add the tools downloaded by conan to the path of your terminal, which
will give you access to `arm-none-eabi-gdb`.

Run this command to start GDB and begin debugging:

```bash
arm-none-eabi-gdb build/MinSizeRel/except.elf -ex "target remote :3333" -ex "set mem inaccessible-by-default off"
```

From here run the following gdb commands:

```gdb
load
b main
continue
```

- `load`: loads the elf file into the device
- `b main`: sets a breakpoint at main
- `continue`: runs the code until it reaches main (start and run are not used)

Put a break point at the line number where the `while(true) { continue; }` is
and enter `continue`. When the program stops inspect the `cycles_map` function.

```gdb
print cycles_map
```

The cycles map has the number of cycles required to throw an exception and catch
it. Save this to a file and replace all `, ` (comma with a space) with a new
line character. Import the CSV into a spreadsheet program and copy and paste the
vertical list into the last column of the spreadsheet. And now you have
performance data.

## How to run Size benchmarks

Haven't written this yet.

## Assumptions about software in general

### 1. **Error handlers are rare in code.**

Most of the code written in an application is dedicated to performing work.
It is not dedicated to handling errors.

It would be very rare to find a code base that is composed of mostly (above 50%)
error handling code over productive code.

### 2. **Most errors require context to be handled**

In general, the only way to properly handle an error is to understand exactly
how and why the error was generated and also understands that there is a way to
recover from that error in software, and this requires context.

**Extreme example:** You have a function called `int sum(int a, int b)`. It can
detect overflows. This function could emit the information in some way,
exceptions or result return types, or it can terminate the application.
Termination seems like it should ALWAYS be the wrong choice because:

1. This function is making an assumption that the application can tolerate
   terminate being called as a result of this function.
2. Raising the risk of calling this function with invalid inputs, requiring the
   developer to add additional checks before calling the function, or wrapping
   the function to detect potential overflows and emitting an error, before
   calling this function. This defeats the purpose of the original function.

Typically, what the developer wants is to be allow to choose to ignore or
handle this error rather than letting the library make critical decision about
the application.

### 3. **Error information tends to be more meaningful at higher stack frame.**

The higher the call frame, the more context about the program is known. The
highest call frame of an application is `main()`. Developers writing their
`main()` function have full understanding of what they set out to do in their
application, thus main has the MOST context regarding what to do when
errors occur and how to handle them.

`main()` could be too high up the stack in cases where main runs the real
application function or it simply spawns a bunch of threads. In which case,
the application function or the threads would be the functions with the most
context about the execution of the function and would be the best places to
handle errors.

It may not always be the highest stack, but some starting stack frame has the
most context regarding handling errors for its call stack.

### 4. **Errors are exceptional situations**

An 64-bit integer overflow, when dealing with real numbers, is a very
exceptional case. Out of bounds access are exceptional, if not simply a
bug in the program. Speaking to a sensor over I2C should almost always work
after the first time communication is established.

## Costs

All tested on a Cortex M4 MCU (lpc4078), using ARM GNU GCC 12.2.1.

### 💾 Storage Costs

- Exceptions:
  - Enabling exceptions: 5005 bytes
  - catch block: TBD
  - catching a new type: TBD
  - throwing a type: TBD
  - throwing a new type: TBD
- `Result<T,E>`:
  - Enabling/using std::expected: TBD
  - Handling an expected value: TBD (should be 0 bytes)
  - Returning std::unexpected: TDB
  - Checking & returning an unexpected value up a level: TBD
  - Returning a new error object

### ⏱️ Time Costs

All tests are conducted with call depths of 1, 2, 4, 8, 10, 16, 32, 50, 64,
and 100. Results will be in the number of CPU cycles, NOT in time as time can
be relative to the CPU operating frequency. With cycles, the amount of time
between an error being emitted and handled by dividing the number of cycles
by the CPU operating frequency.

NOTE: the size of an exception object does not affect the speed in which an
exception is thrown beyond constructing the object. The size of the object does
matter to std::expected. The inheritance hierarchy of an error object returned
using std::unexpected does not affect the speed of returning the object, but
this can greatly affect the speed in which a catch statement can be found.

- Exceptions:
  - Throwing T, catching T, where T is a trivially destructible object
  - Throwing T, catching T*, where T is a trivially destructible object
  - Throwing V, catching I, where I is an interface and V implements I
  - Throwing W, catching E, where E is some base type of W but W has more than
    2 bases (should be the slowest).
- Result:
  - std::unexpected(T) where sizeof(T) == 4 bytes
  - std::unexpected(U) where sizeof(U) > 65 bytes (calls memcpy)
  - std::unexpected(W) where sizeof(W) == 8 bytes
  - std::unexpected(V) where V is a `std::unique_ptr<I>`, where I is an
    interface V implements I.

### 🧠 Memory Costs (RAM)

- Exceptions:
  - Amount of allocated memory (statically or dynamically) when throwing an
    exception.
  - Amount of .data/.bss memory taken up
  - Stack required to run libunwind routines after throw (use stack watermark).
- Result:
  - Amount of additional stack memory used to support result types

## ⚖️ Factors that contribute to code size

### Error transport mechanism

#### ✅ Exception

Exceptions utilize an algorithm along with some slight code instrumentation in
order to manage the task of bringing an error object up to a catch statement,
and running all necessary destructors on its way up to the catch. The cost for
the unwinding mechanism is a fixed cost. As a project gets larger, the
percentage of the mechanism relative to the overall project gets smaller.

We've been capable of getting the total cost of the error transport mechanism,
in Arm Gnu GCC 12.2.1, down to 5005 bytes.

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

If the device you are working with has flash below 32kB, then
result return types can be a decent alternative. Although, in such situations
where error handling will be sparse, it may also be a good idea to simply save
error information to a region of RAM that will persist and terminate/reset the
controller.

### Number of types thrown/unexpected

#### ❌ Exceptions

Each thrown type gets its own type info object created. Along with the
`<typeinfo name for X>`, where `X` is the name of the string literal mangled
name of the type. This string information is inaccessible to programs using
`-fno-rtti`. Each type info object occupy's a place in the `.rodata` region of
the binary. The address of that type info object is compared to the address of
the type info object in the catch statement. Note that the name of the type is
not used for comparisons as that would be too slow. The longer the type's name,
the larger that type info is. This cost is only paid once, so the same object
can be thrown multiple times without generating additional type info objects.

**How to fix this for exceptions?** Patch GCC to add support for
`-fstrip-typeinfo-name`, which would strip out type info type names when
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

#### ✅ Exceptions when they work well

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

#### ❌ Exceptions when they work poorly

#### 🟡 `Result<T,E>`

TBD

## 🏎️ Factors that contribute to happy path performance

### Limitations

TBD

### Benefits of

TBD

## Tricks of the trade

### Weakening symbols so they can be overridden

```bash
arm-none-eabi-objcopy \
/Users/kammce/.conan2/p/b/arm-g788a41ed25167/p/bin/bin/../lib/gcc/arm-none-eabi/12.2.1/thumb/v7e-m+fp/hard/libgcc.a \
--globalize-symbol=search_EIT_table --weaken-symbol=search_EIT_table \
/Users/kammce/.conan2/p/b/arm-g788a41ed25167/p/bin/bin/../lib/gcc/arm-none-eabi/12.2.1/thumb/v7e-m+fp/hard/libgcc.a
```

## :busts_in_silhouette: Contributing

See [`CONTRIBUTING.md`](CONTRIBUTING.md) for details.

## License

Apache 2.0; see [`LICENSE`](LICENSE) for details.

## Disclaimer

This project is not an official Google project. It is not supported by
Google and Google specifically disclaims all warranties as to its quality,
merchantability, or fitness for a particular purpose.
