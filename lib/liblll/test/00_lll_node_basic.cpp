/*
 * John Andersen
 * File: liblll/test/lll_node_basic.cpp
*/
#include "lll.h"

int test_lll_node_basic_add() {
    lll_node_basic head;
    lll_node_basic * added = NULL;
    head.add(added);
    MACRO_TEST_CANT_EQ(added, NULL);
    delete added;
    return EXIT_SUCCESS;
}

int test_lll_node_basic_remove_increasing() {
    lll_node_basic head;
    lll_node_basic * added = NULL;
    const int to_remove = 10;
    int i;
    for (i = 0; i < to_remove; ++i) {
        MACRO_TEST_CANT_EQ(head.add(), NULL);
    }
    for (i = 1; i <= to_remove; ++i) {
        MACRO_TEST_EQ(head.remove(1), true);
    }
    return EXIT_SUCCESS;
}

int test_lll_node_basic_remove_decreasing() {
    lll_node_basic head;
    lll_node_basic * added = NULL;
    const int to_remove = 10;
    int i;
    for (i = 0; i < to_remove; ++i) {
        MACRO_TEST_CANT_EQ(head.add(), NULL);
    }
    for (i = to_remove; i > 0; --i) {
        MACRO_TEST_EQ(head.remove(i), true);
    }
    return EXIT_SUCCESS;
}

int test_lll_node_basic_remove_all() {
    lll_node_basic head;
    lll_node_basic * added = NULL;
    const int to_remove = 10;
    int i;
    for (i = 0; i < to_remove; ++i) {
        head.add();
    }
    MACRO_TEST_EQ(head.remove_all(), to_remove);
    return EXIT_SUCCESS;
}

int test_lll_node_basic_remove_self() {
    lll_node_basic * head = new lll_node_basic;
    MACRO_TEST_EQ(head->remove_self(head), false);
    MACRO_TEST_POINTER_EQ(head, NULL);
    return EXIT_SUCCESS;
}

int test_lll_node_basic_get_index0() {
    lll_node_basic head;
    lll_node_basic * getnode = NULL;
    MACRO_TEST_EQ(head.get(0, getnode), true);
    MACRO_TEST_POINTER_EQ(getnode, &head);
    return EXIT_SUCCESS;
}

int test_lll_node_basic_get() {
    lll_node_basic head;
    lll_node_basic * added = NULL;
    lll_node_basic * getnode = NULL;
    MACRO_TEST_EQ(head.add(added), true);
    MACRO_TEST_EQ(head.get(1, getnode), true);
    MACRO_TEST_POINTER_EQ(getnode, added);
    MACRO_TEST_EQ(head.remove_all(), 1);
    return EXIT_SUCCESS;
}
