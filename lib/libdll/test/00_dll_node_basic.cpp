/*
 * John Andersen
 * File: libdll/test/dll_node_basic.cpp
*/
#include "dll.h"

#define lnb dll_node_basic

int test_dll_node_basic_add() {
    lnb head;
    lnb * added = head.add();
    MACRO_TEST_CANT_EQ(added, NULL);
    delete added;
    return EXIT_SUCCESS;
}

int test_dll_node_basic_remove_increasing() {
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

int test_dll_node_basic_remove_decreasing() {
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

int test_dll_node_basic_remove_all() {
    lnb head;
    const int to_remove = 10;
    int i;
    for (i = 0; i < to_remove; ++i) {
        head.add();
    }
    MACRO_TEST_EQ(head.remove_all(), to_remove);
    return EXIT_SUCCESS;
}

int test_dll_node_basic_remove_self() {
    lnb * head = new lnb;
    MACRO_TEST_POINTER_EQ(head->remove_self(head), NULL);
    MACRO_TEST_POINTER_EQ(head, NULL);
    return EXIT_SUCCESS;
}

int test_dll_node_basic_get_index0() {
    lnb head;
    MACRO_TEST_POINTER_EQ(head.get(0), &head);
    return EXIT_SUCCESS;
}

int test_dll_node_basic_get() {
    lnb head;
    lnb * added = NULL;
    const int to_get = 10;
    int i;
    for (i = 1; i < to_get + 1; ++i) {
        added = head.add();
        MACRO_TEST_CANT_EQ(added, NULL);
        MACRO_TEST_CANT_EQ(head.get(i), NULL);
        MACRO_TEST_POINTER_EQ(head.get(i), added);
    }
    int num_removed = head.remove_all();
    MACRO_TEST_EQ(num_removed, to_get);
    return EXIT_SUCCESS;
}

int test_dll_node_basic_copy() {
    lnb head;
    lnb copy;
    lnb * added = NULL;
    const int to_get = 10;
    int i;
    for (i = 1; i < to_get + 1; ++i) {
        added = head.add();
        MACRO_TEST_CANT_EQ(added, NULL);
        MACRO_TEST_CANT_EQ(head.get(i), NULL);
        MACRO_TEST_POINTER_EQ(head.get(i), added);
    }
    // Now preform the copy
    copy.copy(head);
    int num_removed = head.remove_all();
    MACRO_TEST_EQ(num_removed, to_get);
    num_removed = copy.remove_all();
    MACRO_TEST_EQ(num_removed, to_get);
    return EXIT_SUCCESS;
}
