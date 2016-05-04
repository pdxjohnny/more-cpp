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
    lll_node_basic * added = NULL;
    const int to_get = 10;
    int i;
    for (i = 0; i < to_get; ++i) {
        added = list.add();
        MACRO_TEST_CANT_EQ(added, NULL);
        MACRO_TEST_CANT_EQ(list.get(i), NULL);
        MACRO_TEST_POINTER_EQ(list.get(i), added);
    }
    return EXIT_SUCCESS;
}

int test_lll_basic_operator_subscript() {
    lll_basic list;
    const int to_remove = 10;
    lll_node_basic * added = list[to_remove];
    MACRO_TEST_CANT_EQ(added, NULL);
    lll_node_basic * to_get = list.get(to_remove);
    MACRO_TEST_POINTER_EQ(added, to_get);
    int num_removed = list.remove_all();
    // We need to add one to to_remove because index ten is
    // 0,1,2,3,4,5,6,7,8,9,10 so there are 11 numbers
    MACRO_TEST_EQ(num_removed, to_remove + 1);
    return EXIT_SUCCESS;
}
