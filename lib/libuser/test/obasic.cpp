#include "user.h"

int test_user_obasic_output() {
    // Create the basic user and send some output to it
    user::obasic test;
    test << "Hello this is ostream reporting\n";
    return EXIT_SUCCESS;
}
