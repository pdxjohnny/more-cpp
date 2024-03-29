/*
 * John Andersen
 * File: liblll/test/lll_node<int>.cpp
*/
#include "lll.h"

int test_lll_node_add() {
    lll_node<int> head;
    lll_node<int> * added = (lll_node<int> *)head.add();
    MACRO_TEST_CANT_EQ(added, NULL);
    delete added;
    return EXIT_SUCCESS;
}

int test_lll_node_remove_increasing() {
    lll_node<int> head;
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

int test_lll_node_remove_decreasing() {
    lll_node<int> head;
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

int test_lll_node_remove_all() {
    lll_node<int> head;
    const int to_remove = 10;
    int i;
    for (i = 0; i < to_remove; ++i) {
        head.add();
    }
    MACRO_TEST_EQ(head.remove_all(), to_remove);
    return EXIT_SUCCESS;
}

int test_lll_node_remove_self() {
    lll_node_basic * head = new lll_node<int>;
    MACRO_TEST_POINTER_EQ(head->remove_self(head), NULL);
    MACRO_TEST_POINTER_EQ(head, NULL);
    return EXIT_SUCCESS;
}

int test_lll_node_get_index0() {
    lll_node<int> head;
    MACRO_TEST_POINTER_EQ(head.get(0), &head);
    return EXIT_SUCCESS;
}

int test_lll_node_get() {
    lll_node<int> head;
    lll_node<int> * a = (lll_node<int> *)head.add();
    MACRO_TEST_POINTER_EQ(head.get(1), a);
    MACRO_TEST_EQ(head.remove_all(), 1);
    return EXIT_SUCCESS;
}

int test_lll_node_correct_data() {
    const int value = 42;
    lll_node<int> head;
    head.value() = value;
    const int to_remove = 10;
    int i;
    for (i = 0; i < to_remove; ++i) {
        ((lll_node<int> *)head.add())->value() = i + 1;
    }
    for (i = to_remove; i > 0; --i) {
        MACRO_TEST_EQ(((lll_node<int> *)head.get(i))->value(), i);
    }
    MACRO_TEST_EQ(head.value(), value);
    MACRO_TEST_EQ(head.remove_all(), to_remove);
    return EXIT_SUCCESS;
}
