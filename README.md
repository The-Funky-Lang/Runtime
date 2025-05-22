Runtime Module - Entry & Defines
================================

This document covers the runtime entry point integration and platform/build configuration defines bridging between Funky and C.

* * *

Entry Point (`entry.fnky` + `c/entry.c`)
----------------------------------------

### `RUNTIME_ENTRYPOINT(argc: i32, argv: ^[]str) -> i32`

*   The main entry function for the Funky runtime.
*   Marked with `@INLINE_FUNCTION_C_FLAG@` which means it will be transpiled as an **inline** function in C.
*   Captures command-line arguments into global variables:
    *   `ARG_C: i32` — argument count.
    *   `ARG_V: ^[]str` — argument values (array of strings).
*   Calls the user-defined `entry()` function that starts the actual program logic.
*   Imported from `c/entry.c` which contains the C `main` function.

#### C counterpart (`c/entry.c`):

    int main(int argc, char *argv[]) {
        return RUNTIME_ENTRYPOINT(argc, argv);
    }
    

* * *

Defines Module (`defines.fnky` + `c/defines.c`)
-----------------------------------------------

### Purpose

Bridges compile-time platform and build configuration constants from C to Funky.

### Mapped constants

*   `IS_DEBUG_BUILD: bool`
    *   `true` (1) if compiled with debug flags (`_DEBUG` or `DEBUG`).
    *   `false` (0) otherwise.
*   `OS_NAME_STR: str`
    *   Platform name as a string, e.g., `"Windows"`, `"Linux"`, `"macOS"`, `"Unix"`, or `"Unknown OS"`.

### Source C macros (`c/defines.c`):

    #if _DEBUG || DEBUG
    #define IS_DEBUG 1
    #else
    #define IS_DEBUG 0
    #endif
    
    #if defined(_WIN32) || defined(_WIN64)
    #define OS_STRING "Windows"
    #elif defined(__APPLE__) && defined(__MACH__)
    #define OS_STRING "macOS"
    #elif defined(__linux__)
    #define OS_STRING "Linux"
    #elif defined(__unix__)
    #define OS_STRING "Unix"
    #else
    #define OS_STRING "Unknown OS"
    #endif
    

* * *

Usage Notes
-----------

*   The runtime entry point allows Funky to be executed as a native program with command-line arguments.
*   The defines module allows Funky code to adapt behavior based on the OS and debug status.
*   The `C_import` directive links the relevant C source files seamlessly.
*   The user must provide the `entry()` function in Funky that contains program logic.

* * *