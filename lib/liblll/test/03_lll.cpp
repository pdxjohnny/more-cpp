/*
 * John Andersen
 * File: liblll/test/lll_node_basic.cpp
*/
#include "lll.h"

int test_lll_add() {
    lll<int> list;
    MACRO_TEST_CANT_EQ(list.add(), NULL);
    return EXIT_SUCCESS;
}

int test_lll_remove() {
    lll<int> list;
    MACRO_TEST_CANT_EQ(list.add(), NULL);
    bool removed = list.remove(0);
    MACRO_TEST_EQ(removed, true);
    return EXIT_SUCCESS;
}

int test_lll_remove_all() {
    lll<int> list;
    const int to_remove = 10;
    int i;
    for (i = 0; i < to_remove; ++i) {
        MACRO_TEST_CANT_EQ(list.add(), NULL);
    }
    int num_removed = list.remove_all();
    MACRO_TEST_EQ(num_removed, to_remove);
    return EXIT_SUCCESS;
}

int test_lll_get() {
    lll<int> list;
    const int to_get = 10;
    int i;
    for (i = 0; i < to_get; ++i) {
        MACRO_TEST_CANT_EQ(list.add(), NULL);
        MACRO_TEST_CANT_EQ(list.get(i), NULL);
    }
    return EXIT_SUCCESS;
}

int test_lll_operator_subscript() {
    lll<int> list;
    const int to_remove = 10;
    lll_node_basic * added = list[to_remove];
    MACRO_TEST_CANT_EQ(added, NULL);
    lll_node_basic * to_get = list.get(to_remove);
    MACRO_TEST_POINTER_EQ(added, to_get);
    int num_removed = list.remove_all();
    MACRO_TEST_EQ(num_removed, to_remove);
    return EXIT_SUCCESS;
}
