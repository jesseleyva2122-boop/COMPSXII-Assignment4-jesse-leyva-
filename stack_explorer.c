/* Stack Explorer Assignment - Jesse Leyva
 * Inputs in these demonstrations are small, nonnegative integers.
 */
#include <stdio.h>
#include <string.h>

int max_depth = 0;
static int factorial_depth = 0;
static int trace_fibonacci = 1;
static unsigned long fibonacci_calls = 0;

/* PART 1: BASIC RECURSION */
int factorial(int n) {
    int result;
    ++factorial_depth;
    printf("%*sEntering factorial(%d) [depth %d]\n",
           (factorial_depth - 1) * 2, "", n, factorial_depth);
    if (n <= 1) {
        printf("%*sBase case reached\n", (factorial_depth - 1) * 2, "");
        result = 1;
    } else {
        result = n * factorial(n - 1);
    }
    printf("%*sReturning from factorial(%d) = %d\n",
           (factorial_depth - 1) * 2, "", n, result);
    --factorial_depth;
    return result;
}

/* PART 2: STACK DEPTH TRACKING. Start at depth 1 to count active frames. */
int fibonacci(int n, int depth) {
    int result;
    ++fibonacci_calls;
    if (depth > max_depth) {
        max_depth = depth;
    }
    if (trace_fibonacci) {
        printf("%*sEntering fibonacci(%d), depth %d\n", (depth - 1) * 2, "", n, depth);
    }
    if (n <= 1) {
        result = n;
    } else {
        int left = fibonacci(n - 1, depth + 1);
        int right = fibonacci(n - 2, depth + 1);
        result = left + right;
    }
    if (trace_fibonacci) {
        printf("%*sReturning fibonacci(%d) = %d, depth %d\n",
               (depth - 1) * 2, "", n, result, depth);
    }
    return result;
}

/* PART 3: INTENTIONAL STACK OVERFLOW AND FIX */
void infinite_recursion(int n) {
    /* Indirection and work after the call prevent tail-call optimization
       from turning this experiment into a constant-stack loop. */
    void (*volatile next_call)(int) = infinite_recursion;
    volatile int frame_value = n;
    printf("Call %d\n", n);
    next_call(n + 1); /* Deliberately no base case. */
    printf("Returning from call %d\n", frame_value);
}

void safe_recursion(int n, int depth_limit) {
    printf("Call %d\n", n);
    if (n >= depth_limit) {
        printf("Stopping at max depth\n");
        return;
    }
    safe_recursion(n + 1, depth_limit);
}

/* PART 4: FUNCTION POINTERS AND CALLBACKS */
int double_value(int n) { return n * 2; }
int square_value(int n) { return n * n; }
int negate_value(int n) { return -n; }

void process_array(int *array, int size, int (*callback)(int)) {
    if (array == NULL || callback == NULL || size < 0) {
        printf("Invalid array or callback\n");
        return;
    }
    for (int i = 0; i < size; ++i) {
        printf("%d -> %d\n", array[i], callback(array[i]));
    }
}

/* PART 5: EVENT CALLBACK SYSTEM */
#define MAX_CALLBACKS 10
typedef struct EventSystem {
    void (*callbacks[MAX_CALLBACKS])(int);
    int callback_count;
} EventSystem;

void event_system_init(EventSystem *es) {
    if (es == NULL) { return; }
    es->callback_count = 0;
    for (int i = 0; i < MAX_CALLBACKS; ++i) {
        es->callbacks[i] = NULL;
    }
}

void event_system_register(EventSystem *es, void (*callback)(int)) {
    if (es == NULL || callback == NULL) {
        printf("Invalid event system or callback\n");
        return;
    }
    if (es->callback_count >= MAX_CALLBACKS) {
        printf("Max callbacks reached\n");
        return;
    }
    es->callbacks[es->callback_count++] = callback;
    printf("Callback registered\n");
}

void event_system_trigger(EventSystem *es, int event_value) {
    if (es == NULL) { return; }
    printf("Triggering %d callbacks with value %d\n", es->callback_count, event_value);
    for (int i = 0; i < es->callback_count; ++i) {
        es->callbacks[i](event_value);
    }
}

void on_score_update(int score) {
    printf("  Score callback: New score is %d\n", score);
}
void on_score_display(int score) {
    printf("  Display callback: Updating scoreboard to %d\n", score);
}
void on_level_change(int level) {
    printf("  Level callback: Now entering level %d\n", level);
}
void on_health_change(int health) {
    printf("  Health callback: Health is now %d\n", health);
}

int main(int argc, char **argv) {
    /* Isolate the crash so it does not interrupt the normal demonstrations. */
    if (argc == 2 && strcmp(argv[1], "--overflow") == 0) {
        setvbuf(stdout, NULL, _IONBF, 0);
        printf("Attempting infinite recursion (intentional crash)...\n");
        infinite_recursion(0);
        return 0;
    }
    if (argc > 1) {
        fprintf(stderr, "Usage: %s [--overflow]\n", argv[0]);
        return 1;
    }
    printf("STACK EXPLORER: Function Call Mechanics\n");
    printf("\n--- Part 1: Factorial with Stack Visualization ---\n");
    int result = factorial(5);
    printf("factorial(5) = %d\n", result);
    result = factorial(10);
    printf("factorial(10) = %d\n", result);

    printf("\n--- Part 2: Fibonacci with Depth Tracking ---\n");
    int inputs[] = {10, 20, 30};
    for (int i = 0; i < 3; ++i) {
        max_depth = 0;
        fibonacci_calls = 0;
        /* Print every call for 10; summarize larger runs to avoid millions
           of output lines. Depth and call counting remain enabled. */
        trace_fibonacci = (inputs[i] == 10);
        result = fibonacci(inputs[i], 1);
        printf("fibonacci(%d) = %d; maximum depth = %d; total calls = %lu\n",
               inputs[i], result, max_depth, fibonacci_calls);
    }
    printf("\n--- Part 3: Stack Overflow Demo ---\n");
    printf("Run separately with --overflow to observe the intentional crash.\n");
    printf("\n--- Part 3: Safe Recursion (Fixed Version) ---\n");
    safe_recursion(0, 10);

    printf("\n--- Part 4: Function Pointers and Callbacks ---\n");
    int array[] = {1, 2, 3, 4, 5};
    printf("Double values:\n");
    process_array(array, 5, double_value);
    printf("Square values:\n");
    process_array(array, 5, square_value);
    printf("Negate values:\n");
    process_array(array, 5, negate_value);

    printf("\n--- Part 5: Event System ---\n");
    /* Each instance represents a different event and its listeners. */
    EventSystem score_event, level_event, health_event;
    event_system_init(&score_event);
    event_system_init(&level_event);
    event_system_init(&health_event);
    event_system_register(&score_event, on_score_update);
    event_system_register(&health_event, on_health_change);
    event_system_register(&score_event, on_score_display);
    event_system_register(&level_event, on_level_change);
    event_system_trigger(&score_event, 100);
    event_system_trigger(&level_event, 2);
    event_system_trigger(&health_event, 75);
    printf("\nStack exploration complete!\n");
    return 0;
}
