# Stack Explorer Assignment
Jesse Leyva — Computer Science XII

## Files
- `stack_explorer.c`: All five assignment parts implemented.
- `reflection.md`: Written analysis of the observed results.

## Compile and run
```bash
gcc -std=c11 -Wall -Wextra -Wpedantic -Werror stack_explorer.c -o stack_explorer
./stack_explorer
```
On Windows, use `-o stack_explorer.exe` and run `stack_explorer.exe`.

The normal run completes all demonstrations. Factorial traces inputs 5 and 10.
Fibonacci traces input 10 and summarizes inputs 20 and 30 to avoid millions of
output lines. Tracking remains active on every call.

| Input | Fibonacci result | Maximum depth (starting at 1) | Total calls |
| --- | --- | --- | --- |
| 10 | 55 | 10 | 177 |
| 20 | 6765 | 20 | 21891 |
| 30 | 832040 | 30 | 2692537 |

Fibonacci's call count grows exponentially; its maximum simultaneous stack depth
is linear. Factorial(10) also reaches 10 recursive frames.

The array processor prints doubled, squared, and negated values of 1 through 5.
Separate score, level, and health events dispatch to their registered listeners;
the score event demonstrates two different callbacks for one event.
These integer examples use small inputs that fit in `int`.

## Intentional overflow experiment
```bash
./stack_explorer --overflow
```
This mode deliberately has no base case and is expected to crash. It is isolated
from the normal run. The observed Linux test used a 1 MiB stack limit and terminated
with SIGSEGV (segmentation fault). The call count before failure depends on the
platform, stack size, and compiler. `safe_recursion(0, 10)` shows the bounded fix.

## Validation
- Strict C11 compilation with warnings treated as errors passed.
- Normal execution and an assertion harness passed AddressSanitizer and
  UndefinedBehaviorSanitizer checks (leak detection disabled because the execution
  environment does not support LeakSanitizer).
- Checked factorial/Fibonacci values, depth and call counts, array callbacks,
  empty events, null callback rejection, and the 10-callback registration limit.
- Separately confirmed the intentional overflow terminates with SIGSEGV.
