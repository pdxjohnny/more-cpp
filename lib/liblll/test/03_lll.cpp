/*
 * John Andersen
 * File: liblll/test/lll_node<int>.cpp
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
    lll_node<int> * added = (lll_node<int> *)list.get_extend(to_remove);
    MACRO_TEST_CANT_EQ(added, NULL);
    lll_node<int> * to_get = (lll_node<int> *)list.get(to_remove);
    MACRO_TEST_POINTER_EQ(added, to_get);
    int num_removed = list.remove_all();
    // Add one because index 10 means 0 through 10 so 11 nodes
    MACRO_TEST_EQ(num_removed, to_remove + 1);
    return EXIT_SUCCESS;
}

int test_lll_correct_data() {
    const int value = 42;
    lll<int> head;
    head[0] = value;
    const int to_remove = 10;
    int i;
    for (i = 1; i < to_remove; ++i) {
        head[i] = i;
    }
    for (i = to_remove - 1; i > 0; --i) {
        MACRO_TEST_EQ(head[i], i);
    }
    MACRO_TEST_EQ(head[0], value);
    MACRO_TEST_EQ(head.remove_all(), to_remove);
    return EXIT_SUCCESS;
}
