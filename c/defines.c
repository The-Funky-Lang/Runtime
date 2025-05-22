
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
