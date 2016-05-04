/*
 * John Andersen
 * File: liblll/test/lll_node_basic.cpp
*/
#include "lll.h"

int test_lll_basic_add() {
    lll_basic list;
    lll_node_basic * added = NULL;
    MACRO_TEST_EQ(list.add(added), true);
    return EXIT_SUCCESS;
}

int test_lll_basic_remove() {
    lll_basic list;
    lll_node_basic * added = NULL;
    MACRO_TEST_EQ(list.add(added), true);
    bool removed = list.remove(0);
    MACRO_TEST_EQ(removed, true);
    return EXIT_SUCCESS;
}

int test_lll_basic_remove_all() {
    lll_basic list;
    lll_node_basic * added = NULL;
    const int to_remove = 10;
    int i;
    for (i = 0; i < to_remove; ++i) {
        MACRO_TEST_EQ(list.add(added), true);
    }
    int num_removed = list.remove_all();
    MACRO_TEST_EQ(num_removed, to_remove);
    return EXIT_SUCCESS;
}

int test_lll_basic_get() {
    lll_basic list;
    lll_node_basic * added = NULL;
    lll_node_basic * getnode = NULL;
    const int to_get = 10;
    int i;
    for (i = 0; i < to_get; ++i) {
        MACRO_TEST_EQ(list.add(added), true);
        MACRO_TEST_CANT_EQ(list.get(i, getnode), false);
    }
    return EXIT_SUCCESS;
}

int test_lll_basic_operator_subscript() {
    const int to_remove = 10;
    int num_removed = 0;
    lll_basic list;
    lll_node_basic * added = list[to_remove];
    lll_node_basic * getnode = NULL;
    // Make sure it added
    MACRO_TEST_CANT_EQ(added, NULL);
    MACRO_TEST_EQ(list.get(to_remove, getnode), true);
    MACRO_TEST_POINTER_EQ(added, getnode);
    // Make sure it removes
    num_removed = list.remove_all();
    MACRO_TEST_EQ(num_removed, to_remove);
    return EXIT_SUCCESS;
}
