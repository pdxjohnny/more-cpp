#include "user.h"

int test_user_ibasic_output() {
    char buffer[7];
    buffer[7] = '\0';
    // Create the basic user and send some output to it
    user::obasic test;
    test.get(buffer, 2);
    MACRO_TEST_STR_EQ(buffer, "qqqqqq");
    return EXIT_SUCCESS;
}
