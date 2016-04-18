#include "uber.h"

int test_uber_car_order() {
    // Create the first one
    uber::car * d = new uber::car(1999, "d", "d", "", "");
    // Add them all to the first one
    uber::car * a = (uber::car *)d->add(new uber::car(1999, "a", "a", "", ""));
    uber::car * c = (uber::car *)d->add(new uber::car(1999, "c", "c", "", ""));
    uber::car * b = (uber::car *)d->add(new uber::car(1999, "b", "b", "", ""));
    // Make sure they are in the right order
    uber::car * should_be[] = {
        a,
        b,
        c,
        d,
        NULL
    };
    MACRO_TEST_EQ(c->test_order((circle **)should_be), EXIT_SUCCESS);
    // Remove one from the list
    delete c;
    // Make sure they are in the right order
    uber::car * should_be_2[] = {
        a,
        b,
        d,
        NULL
    };
    MACRO_TEST_EQ(b->test_order((circle **)should_be_2), EXIT_SUCCESS);
    // Delete the list
    b->destroy();
    // Delete the first one
    MACRO_DELETE_IF_NOT_NULL(b);
    return EXIT_SUCCESS;
}

