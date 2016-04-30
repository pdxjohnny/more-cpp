/*
 * John Andersen
 * File: liblll/test/lll_node_basic.cpp
*/
#include "lll.h"

int test_lll_basic_add() {
    lll_basic list;
    MACRO_TEST_CANT_EQ(list.add(), NULL);
    return EXIT_SUCCESS;
}

int test_lll_basic_remove() {
    lll_basic list;
    MACRO_TEST_CANT_EQ(list.add(), NULL);
    bool removed = list.remove(0);
    MACRO_TEST_EQ(removed, true);
    return EXIT_SUCCESS;
}

int test_lll_basic_remove_all() {
    lll_basic list;
    const int to_remove = 10;
    int i;
    for (i = 0; i < to_remove; ++i) {
        MACRO_TEST_CANT_EQ(list.add(), NULL);
    }
    int num_removed = list.remove_all();
    MACRO_TEST_EQ(num_removed, to_remove);
    return EXIT_SUCCESS;
}

int test_lll_basic_get() {
    lll_basic list;
    const int to_get = 10;
    int i;
    for (i = 0; i < to_get; ++i) {
        MACRO_TEST_CANT_EQ(list.add(), NULL);
        MACRO_TEST_CANT_EQ(list.get(i), NULL);
    }
    return EXIT_SUCCESS;
}
