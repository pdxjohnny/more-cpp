/*
 * John Andersen
 * File: libdll/test/dll_node_basic.cpp
*/
#include "dll.h"

int test_dll_basic_add() {
    dll_basic list;
    MACRO_TEST_CANT_EQ(list.add(), NULL);
    return EXIT_SUCCESS;
}

int test_dll_basic_remove() {
    dll_basic list;
    MACRO_TEST_CANT_EQ(list.add(), NULL);
    bool removed = list.remove(0);
    MACRO_TEST_EQ(removed, true);
    return EXIT_SUCCESS;
}

int test_dll_basic_remove_all() {
    dll_basic list;
    const int to_remove = 10;
    int i;
    for (i = 0; i < to_remove; ++i) {
        MACRO_TEST_CANT_EQ(list.add(), NULL);
    }
    int num_removed = list.remove_all();
    MACRO_TEST_EQ(num_removed, to_remove);
    return EXIT_SUCCESS;
}

int test_dll_basic_get() {
    dll_basic list;
    dll_node_basic * added = NULL;
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

int test_dll_basic_operator_subscript() {
    dll_basic list;
    const int to_remove = 10;
    dll_node_basic * added = list[to_remove];
    MACRO_TEST_CANT_EQ(added, NULL);
    dll_node_basic * to_get = list.get(to_remove);
    MACRO_TEST_POINTER_EQ(added, to_get);
    int num_removed = list.remove_all();
    // We need to add one to to_remove because index ten is
    // 0,1,2,3,4,5,6,7,8,9,10 so there are 11 numbers
    MACRO_TEST_EQ(num_removed, to_remove + 1);
    return EXIT_SUCCESS;
}

int test_dll_basic_operator_copy() {
    dll_basic list;
    dll_basic copy;
    const int to_remove = 10;
    // Create all the nodes in list
    dll_node_basic * added = list[to_remove];
    MACRO_TEST_CANT_EQ(added, NULL);
    dll_node_basic * to_get = list.get(to_remove);
    MACRO_TEST_POINTER_EQ(added, to_get);
    // Copy all the nodes to copy
    copy = list;
    // Now remove them all
    int num_removed = list.remove_all();
    MACRO_TEST_EQ(num_removed, to_remove + 1);
    // Make sure the copy has removed the same amount
    num_removed = copy.remove_all();
    MACRO_TEST_EQ(num_removed, to_remove + 1);
    return EXIT_SUCCESS;
}
