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

#define MACRO_TEST(test_name) \
({\
    printf("Running %-60s\r", #test_name);\
    if (test_name() == -1) {\
        printf("Running %-60s[" MACRO_RED " FAILED " MACRO_RESET "]\n", #test_name);\
        exit(errno);\
    }\
    printf("Running %-60s[" MACRO_GREEN "   OK   " MACRO_RESET "]\n", #test_name);\
})

#define MACRO_TEST_EQ(var, should_be) \
({\
    if (var != should_be) {\
        printf(#var " should have been %d but was %-20d\n", should_be, var);\
        return -1;\
    }\
})

#define MACRO_TEST_POINTER_EQ(var, should_be) \
({\
    if (var != should_be) {\
        printf(#var " should have been %p but was %-20p\n", (void *)should_be, (void *)var);\
        return -1;\
    }\
})

#define MACRO_TEST_FLOAT_EQ(var, should_be) \
({\
    if (var != (float)should_be) {\
        printf(#var " should have been %lf but was %-20lf\n", should_be, var);\
        return -1;\
    }\
})

#define MACRO_TEST_DOUBLE_EQ(var, should_be) \
({\
    if (var != (double)should_be) {\
        printf(#var " should have been %lf but was %-20lf\n", should_be, var);\
        return -1;\
    }\
})

#define MACRO_TEST_STR_EQ(var, should_be) \
({\
    if (0 != strcmp(var, should_be)) {\
        printf(#var " should have been " #should_be " but was %-20s\n", var);\
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

