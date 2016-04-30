/*
 * John Andersen
 * File: libmacro/include/libmacro.h
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <time.h>


#define MACRO_RED     "\x1b[31m"
#define MACRO_GREEN   "\x1b[32m"
#define MACRO_YELLOW  "\x1b[33m"
#define MACRO_BLUE    "\x1b[34m"
#define MACRO_MAGENTA "\x1b[35m"
#define MACRO_CYAN    "\x1b[36m"
#define MACRO_RESET   "\x1b[0m"

#define MACRO_NUM_TO_STR 129
#define MACRO_HOURS_TO_MINUTES 60

#define MACRO_PRINT(format, ...) \
({\
    printf(format, __VA_ARGS__);\
})

#define MACRO_PRINT_FILE_LINE(format, ...) \
({\
    MACRO_PRINT("%s:%d    " format, __FILE__, __LINE__, __VA_ARGS__);\
})

#define MACRO_LOG_INT(var) \
({\
    MACRO_PRINT_FILE_LINE(#var ": %d\n", var);\
})

#define MACRO_LOG_POINTER(var) \
({\
    MACRO_PRINT_FILE_LINE(#var ": %p\n", var);\
})

#define MACRO_LOG_STR(var) \
({\
    MACRO_PRINT_FILE_LINE(#var ": %s\n", var);\
})

#define MACRO_TEST_LOG_ERROR(format, ...) \
({\
    MACRO_PRINT_FILE_LINE(MACRO_RED "ERROR" MACRO_RESET ": " format ": %s\n", __VA_ARGS__, strerror(errno));\
})

#define MACRO_LOG_ERROR(format, ...) \
({\
    MACRO_PRINT(MACRO_RED "ERROR" MACRO_RESET ": " format ": %s\n", __VA_ARGS__, strerror(errno));\
})

#define MACRO_LOG_FATAL(format, ...) \
({\
    MACRO_LOG_ERROR(format, __VA_ARGS__);\
    return errno;\
})

#define MACRO_TEST(test_name) \
({\
    MACRO_PRINT("Running %-60s\r", #test_name);\
    if (test_name() == -1) {\
        MACRO_PRINT("Running %-60s[" MACRO_RED " FAILED " MACRO_RESET "]\n", #test_name);\
        if (errno != 0) {\
            exit(errno);\
        }\
        return 1;\
    }\
    MACRO_PRINT("Running %-60s[" MACRO_GREEN "   OK   " MACRO_RESET "]\n", #test_name);\
})

#define MACRO_TEST_CANT_EQ(var, should_be) \
({\
    if (var == should_be) {\
        MACRO_TEST_LOG_ERROR(#var " should not have been %p but was %p", (void *)should_be, (void *)var);\
        return -1;\
    }\
})

#define MACRO_TEST_INT_CANT_EQ(var, should_be) \
({\
    if (var == should_be) {\
        MACRO_TEST_LOG_ERROR(#var " should not have been %d but was %d", should_be, var);\
        return -1;\
    }\
})

#define MACRO_TEST_EQ(var, should_be) \
({\
    if (var != should_be) {\
        MACRO_TEST_LOG_ERROR(#var " should have been %d but was %d", should_be, var);\
        return -1;\
    }\
})

#define MACRO_TEST_POINTER_EQ(var, should_be) \
({\
    if (var != should_be) {\
        MACRO_TEST_LOG_ERROR(#var " should have been %p but was %p", (void *)should_be, (void *)var);\
        return -1;\
    }\
})

#define MACRO_TEST_FLOAT_EQ(var, should_be) \
({\
    if (var != (float)should_be) {\
        MACRO_TEST_LOG_ERROR(#var " should have been %lf but was %lf", should_be, var);\
        return -1;\
    }\
})

#define MACRO_TEST_DOUBLE_EQ(var, should_be) \
({\
    if (var != (double)should_be) {\
        MACRO_TEST_LOG_ERROR(#var " should have been %lf but was %lf", should_be, var);\
        return -1;\
    }\
})

#define MACRO_TEST_MEM_STR_EQ(var, should_be) \
({\
    if (0 != strcmp(var, should_be)) {\
        MACRO_TEST_LOG_ERROR(#var " should have been %s but was %s", should_be, var);\
        return -1;\
    }\
})

#define MACRO_TEST_STR_EQ(var, should_be) \
({\
    if (0 != strcmp(var, should_be)) {\
        MACRO_TEST_LOG_ERROR(#var " should have been " #should_be " but was %s", var);\
        return -1;\
    }\
})

#define MACRO_TEST_STR_EQ_CLEANUP(var, should_be, cleanup) \
({\
    if (0 != strcmp(var, should_be)) {\
        MACRO_TEST_LOG_ERROR(#var " should have been " #should_be " but was %s", var);\
        cleanup;\
        return -1;\
    }\
})

#define MACRO_EQ(var, cant_be) \
({\
    if (var != cant_be) {\
        return -1;\
    }\
})

#define MACRO_CANT_EQ(var, cant_be) \
({\
    if (var == cant_be) {\
        return -1;\
    }\
})

#define MACRO_DELETE_IF_NOT_NULL(var)\
({\
    if (var != NULL) {\
        delete var;\
        var = NULL;\
    }\
})

#define MACRO_DELETE_ARRAY_IF_NOT_NULL(var)\
({\
    if (var != NULL) {\
        delete[] var;\
        var = NULL;\
    }\
})

#define MACRO_STRCPY_IF_NOT_NULL(dest, src)\
({\
    MACRO_DELETE_ARRAY_IF_NOT_NULL(dest);\
    if (src != NULL) {\
        dest = new char[strlen(src) + 1];\
        strcpy(dest, src);\
    }\
})

#define MACRO_STRNCPY_IF_NOT_NULL(dest, src, n)\
({\
    MACRO_DELETE_ARRAY_IF_NOT_NULL(dest);\
    if (src != NULL) {\
        dest = new char[strnlen(src, n - 1) + 1];\
        strncpy(dest, src, n);\
    }\
})

#define MACRO_JOIN_STRING_ARRAY(dest, src, delim, if_null)\
({\
    int length = strings::join_length(src, delim, if_null);\
    dest = new char [length];\
    strings::join(dest, src, delim, if_null, length);\
})

#define MACRO_DELETE_ARRAY_OF_STRINGS(dest)\
({\
    int i;\
    for (i = 0; dest[i] != NULL; ++i) {\
        MACRO_DELETE_ARRAY_IF_NOT_NULL(*(dest[i]));\
        MACRO_DELETE_IF_NOT_NULL(dest[i]);\
    }\
    MACRO_DELETE_ARRAY_IF_NOT_NULL(dest);\
})

