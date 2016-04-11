#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <time.h>

#include <librbt.h>


#define RBT_TEST(test_name) \
({\
    if (test_name() == -1) {\
        printf(#test_name " exited with status %d\n", errno);\
        exit(errno);\
    }\
})

#define RBT_TEST_EQ(var, should_be) \
({\
    if (var != should_be) {\
        printf(#var " should have been " #should_be " but was \"%x\"\n", var);\
    }\
})

#define RBT_TEST_FLOAT_EQ(var, should_be) \
({\
    if (var != should_be) {\
        printf(#var " should have been " #should_be " but was \"%lf\"\n", var);\
    }\
})

#define RBT_TEST_STR_EQ(var, should_be) \
({\
    if (0 != strcmp(var, should_be)) {\
        printf(#var " should have been " #should_be " but was \"%s\"\n", var);\
    }\
})

