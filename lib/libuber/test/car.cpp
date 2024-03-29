/*
 * John Andersen
 * File: libuber/test/car.cpp
 * Tests that the car class is working
*/

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

int test_uber_car_unique_make_models() {
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

int test_uber_car_save() {
    // Create the first one
    uber::car car(1999, "a", "b", "c", "d");
    // Set up the pipe
    int fd[2];
    pipe(fd);
    // Create the buffer
    char buffer[500];
    // Write to the pipe
    car.save(fd[1]);
    // Check that we wrote what we expected to write
    strings::readline(fd[0], buffer, 500);
    MACRO_TEST_STR_EQ(buffer, "1999, a, b, c, d");
    return EXIT_SUCCESS;
}

int test_uber_car_get() {
    // Create the first one
    uber::car * d = new uber::car(1999, "d", "d", "", "");
    // Add them all to the first one
    uber::car * a = (uber::car *)d->add(new uber::car(1999, "a", "a", "plate", "vin"));
    // Make sure they are in the right order
    uber::car * should_be[] = {
        a,
        d,
        NULL
    };
    MACRO_TEST_EQ(d->test_order((circle **)should_be), EXIT_SUCCESS);
    // Find a match
    uber::car * find = new uber::car(0, "a", "a", "", "");
    uber::car * found = NULL;
    found = (uber::car *)a->get(find);
    MACRO_TEST_CANT_EQ(found, NULL);
    MACRO_TEST_EQ(found->year(), 1999);
    MACRO_TEST_STR_EQ(found->make(), "a");
    MACRO_TEST_STR_EQ(found->model(), "a");
    MACRO_TEST_STR_EQ(found->plate_number(), "plate");
    MACRO_TEST_STR_EQ(found->vin(), "vin");
    MACRO_DELETE_IF_NOT_NULL(find);
    MACRO_DELETE_IF_NOT_NULL(found);
    // Make sure that the one we found was removed
    uber::car * should_be_2[] = {
        d,
        NULL
    };
    MACRO_TEST_EQ(d->test_order((circle **)should_be_2), EXIT_SUCCESS);
    // Delete the list
    d->destroy();
    // Delete the first one
    MACRO_DELETE_IF_NOT_NULL(d);
    return EXIT_SUCCESS;
}

int test_uber_car_get_not_found() {
    // Create the first one
    uber::car * d = new uber::car(1999, "d", "d", "", "");
    // Add them all to the first one
    uber::car * a = (uber::car *)d->add(new uber::car(1999, "a", "a", "plate", "vin"));
    // Make sure they are in the right order
    uber::car * should_be[] = {
        a,
        d,
        NULL
    };
    MACRO_TEST_EQ(d->test_order((circle **)should_be), EXIT_SUCCESS);
    // Find a match
    uber::car * find = new uber::car(0, "x", "x", "", "");
    uber::car * found = NULL;
    found = (uber::car *)a->get(find);
    MACRO_TEST_POINTER_EQ(found, NULL);
    // Make sure that the one we found was removed
    uber::car * should_be_2[] = {
        a,
        d,
        NULL
    };
    MACRO_TEST_EQ(d->test_order((circle **)should_be_2), EXIT_SUCCESS);
    // Delete the list
    d->destroy();
    // Delete the first one
    MACRO_DELETE_IF_NOT_NULL(d);
    return EXIT_SUCCESS;
}
