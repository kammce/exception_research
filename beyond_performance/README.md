# How to go beyond error codes

How can exceptions be faster than result types?

1. Exceptions only have to construct the error object once and do not have to
   interact until it is delivered to a catch statement. Even if the error object
   is a single byte, it still needs to be transported/copied up the stack.
2. Does not need to maintain CPU state for all frames, just the one before the
   the true catch handler is invoked. All of the previous state was saved on
   the stack of the previous function.
3. Due to being on the exceptional path, there is not need to recompute if a
   return object is on the error or normal path.

## Next generation of exception handling

### Design parameters

1. Static applications
2. Embedded systems
3. Single threaded (will add multi-thread support later with atomics)
4. Leverages frame pointers
5. Assumes catch statements do not throw inside of their scope

### Estell Exceptions

Implementations for:

1. `__cxa_allocate_exception`: C++ ABI function for allocating exceptions
2. `__cxa_throw`: C++ ABI function for throwing an exception
3. `__fast_iterative_unwind`: an inline function that iterates up the stack using the frame pointers to find a function that has a non-trivial cleanup.
4. `__unwind_execute(_Unwind_Context* context, _unwind_state* unwind_state)`: Unwinds a function using the unwind_state information.
5. `__capture_cpu_state`: inline assemble function that captures the state of the CPU and saves it in a context function.
6. `__cxa_begin_catch`
7. `__cxa_end_catch`
8. `__cxa_end_cleanup`
