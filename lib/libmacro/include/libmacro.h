#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <time.h>


#define MACRO_TEST(test_name) \
({\
    err = test_name();\
    if (err == -1) {\
        printf(#test_name " exited with status %d\n", errno);\
    }\
})

#define MACRO_TEST_EQ(var, should_be) \
({\
    if (var != should_be) {\
        printf(#var " should have been " #should_be " but was \"%x\"\n", var);\
    }\
})

#define MACRO_TEST_FLOAT_EQ(var, should_be) \
({\
    if (var != should_be) {\
        printf(#var " should have been " #should_be " but was \"%lf\"\n", var);\
    }\
})

#define MACRO_TEST_STR_EQ(var, should_be) \
({\
    if (0 != strcmp(var, should_be)) {\
        printf(#var " should have been " #should_be " but was \"%s\"\n", var);\
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

