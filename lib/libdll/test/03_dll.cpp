/*
 * John Andersen
 * File: libdll/test/dll_node<int>.cpp
*/
#include "dll.h"

int test_dll_add() {
    dll<int> list;
    MACRO_TEST_CANT_EQ(list.add(), NULL);
    return EXIT_SUCCESS;
}

int test_dll_remove() {
    dll<int> list;
    MACRO_TEST_CANT_EQ(list.add(), NULL);
    bool removed = list.remove(0);
    MACRO_TEST_EQ(removed, true);
    return EXIT_SUCCESS;
}

int test_dll_remove_all() {
    dll<int> list;
    const int to_remove = 10;
    int i;
    for (i = 0; i < to_remove; ++i) {
        MACRO_TEST_CANT_EQ(list.add(), NULL);
    }
    int num_removed = list.remove_all();
    MACRO_TEST_EQ(num_removed, to_remove);
    return EXIT_SUCCESS;
}

int test_dll_get() {
    dll<int> list;
    const int to_get = 10;
    int i;
    for (i = 0; i < to_get; ++i) {
        MACRO_TEST_CANT_EQ(list.add(), NULL);
        MACRO_TEST_CANT_EQ(list.get(i), NULL);
    }
    return EXIT_SUCCESS;
}

int test_dll_operator_subscript() {
    dll<int> list;
    const int to_remove = 10;
    dll_node<int> * added = (dll_node<int> *)list.get_extend(to_remove);
    MACRO_TEST_CANT_EQ(added, NULL);
    dll_node<int> * to_get = (dll_node<int> *)list.get(to_remove);
    MACRO_TEST_POINTER_EQ(added, to_get);
    int num_removed = list.remove_all();
    // Add one because index 10 means 0 through 10 so 11 nodes
    MACRO_TEST_EQ(num_removed, to_remove + 1);
    return EXIT_SUCCESS;
}

int test_dll_correct_data() {
    const int value = 42;
    dll<int> head;
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

int test_dll_operator_copy() {
    dll<int> list;
    dll<int> copy;
    const int to_remove = 10;
    // Create all the nodes in list
    list[to_remove] = 42;
    int added = list[to_remove];
    MACRO_TEST_EQ(added, 42);
    dll_node<int> * to_get = (dll_node<int> *)list.get(to_remove);
    MACRO_TEST_EQ(added, to_get->value());
    // Initialize all the data
    int i;
    for (i = list.size() - 1; i >= 0; --i) {
        list[i] = i;
    }
    // Copy all the nodes to copy
    copy = list;
    // Make sure all the data is correct
    for (i = list.size() - 1; i >= 0; --i) {
        MACRO_TEST_EQ(copy[i], list[i]);
    }
    // Now remove them all
    int num_removed = list.remove_all();
    MACRO_TEST_EQ(num_removed, to_remove + 1);
    // Make sure the copy has removed the same amount
    num_removed = copy.remove_all();
    MACRO_TEST_EQ(num_removed, to_remove + 1);
    return EXIT_SUCCESS;
}
