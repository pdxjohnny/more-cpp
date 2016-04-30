/*
 * John Andersen
 * File: liblll/test/lll_node_basic.cpp
*/
#include "lll.h"

#define lnb lll_node_basic

int test_lll_node_basic_add() {
    lnb head;
    lnb * added = head.add();
    MACRO_TEST_CANT_EQ(added, NULL);
    delete added;
    return EXIT_SUCCESS;
}

int test_lll_node_basic_remove_increasing() {
    lnb head;
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
    lnb head;
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
    lnb head;
    const int to_remove = 10;
    int i;
    for (i = 0; i < to_remove; ++i) {
        head.add();
    }
    MACRO_TEST_EQ(head.remove_all(), to_remove);
    return EXIT_SUCCESS;
}

int test_lll_node_basic_remove_self() {
    lnb * head = new lnb;
    MACRO_TEST_POINTER_EQ(head->remove_self(head), NULL);
    MACRO_TEST_POINTER_EQ(head, NULL);
    return EXIT_SUCCESS;
}

int test_lll_node_basic_get_index0() {
    lnb head;
    MACRO_TEST_POINTER_EQ(head.get(0), &head);
    return EXIT_SUCCESS;
}

int test_lll_node_basic_get() {
    lnb head;
    lnb * a = head.add();
    MACRO_TEST_POINTER_EQ(head.get(1), a);
    MACRO_TEST_EQ(head.remove_all(), 1);
    return EXIT_SUCCESS;
}
