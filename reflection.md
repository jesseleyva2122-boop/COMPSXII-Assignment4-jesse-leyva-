# Stack Explorer Reflection
Jesse Leyva

## Stack Mechanics

Running factorial helped me understand the order of recursive calls. For factorial(5), the program entered 5, 4, 3, 2, and 1 before returning any results. The indentation moved farther right as each call added another active frame. After the base case, the return messages moved back left, showing results of 1, 2, 6, 24, and 120. Factorial(10) followed the same pattern and returned 3,628,800. Fibonacci also showed calls entering and returning, but it repeatedly explored two branches instead of following just one chain.

The separate overflow test ended with SIGSEGV, a segmentation fault. The test used a one-megabyte stack limit so the crash happened quickly. There was no base case, so calls kept adding frames until the stack could not grow safely. The fixed version stopped at 10 and returned normally.

A stack frame typically holds local variables, saved state, and a return address telling execution where to continue. Parameters may also be stored there, although some are passed in registers. The exact layout depends on the platform and compiler.

## Recursion Costs

With a starting depth of 1, factorial(10) and Fibonacci(10) both reached 10 active recursive frames. Fibonacci made 177 total calls, while factorial made only 10. Fibonacci(20) reached depth 20 with 21,891 calls, and Fibonacci(30) reached depth 30 with 2,692,537 calls. This showed that Fibonacci's total work grows exponentially, but its maximum depth grows linearly. Its branches run sequentially, so every call is not on the stack at once. Both algorithms have linear maximum stack usage, although their individual frame sizes can differ.

Python limits recursion depth to catch excessive recursion before it becomes an uncontrolled stack failure. Without a protective limit, deeply nested calls could exhaust stack space and crash, like the C overflow demonstration. Even a terminating recursive function needs a reasonable depth limit.

## Function Pointers and Callbacks

A function pointer stores the address of a function with a particular signature. Passing that pointer into process_array let the same loop double, square, or negate values. I did not need to rewrite the loop for each operation. The processor called whichever function it received and printed the result for each element.

A paint program could use callbacks for mouse clicks. Clicking a tool button could run a registered handler that selects a brush or starts filling an area. My event system used separate instances for score, level, and health events, and the score event notified two different listeners.

Systems programmers use callbacks because they let reusable code run behavior supplied by another part of a program. The syntax takes more attention, but it keeps event handling flexible and avoids duplicating processing code.
