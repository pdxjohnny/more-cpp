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

int test_uber_unique_make_models() {
    // Create the first one
    uber::car * a = new uber::car(1999, "a", "x", "", "");
    // Add them all to the first one
    a->add(new uber::car(1999, "b", "b", "", ""));
    a->add(new uber::car(1999, "c", "c", "", ""));
    a->add(new uber::car(1999, "b", "q", "", ""));
    a->add(new uber::car(1999, "b", "q", "", ""));
    a->add(new uber::car(1999, "a", "x", "", ""));
    // Make sure that it was correct
    char * umm = NULL;
    char *** umm_join = a->unique_makes_models();
    MACRO_JOIN_STRING_ARRAY(umm, umm_join, " ", "error");
    MACRO_DELETE_ARRAY_OF_STRINGS(umm_join);
    MACRO_TEST_STR_EQ_CLEANUP(umm, "a/x b/b b/q c/c", {
        MACRO_DELETE_ARRAY_IF_NOT_NULL(umm);
        // Delete the list
        a->destroy();
        // Delete the first one
        MACRO_DELETE_IF_NOT_NULL(a);
    });
    MACRO_DELETE_ARRAY_IF_NOT_NULL(umm);
    // Delete the list
    a->destroy();
    // Delete the first one
    MACRO_DELETE_IF_NOT_NULL(a);
    return EXIT_SUCCESS;
}

