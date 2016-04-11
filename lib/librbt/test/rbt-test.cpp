#include "rbt-test.h"

int main (int argc, char ** argv, char ** env) {
    // Run the test function
    RBT_TEST_EQ(rbt_test(), 42);

    // Run all the tests
    // RBT_TEST(test_rbt_something);

    return EXIT_SUCCESS;
}

