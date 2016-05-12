/*
 * John Andersen
 * File: libtree23/test/tree23_node<int>.cpp
*/
#include "tree23.h"

int test_tree23_add() {
    tree23<int> list;
    MACRO_TEST_CANT_EQ(list.add(), NULL);
    return EXIT_SUCCESS;
}

int test_tree23_remove() {
    tree23<int> list;
    MACRO_TEST_CANT_EQ(list.add(), NULL);
    bool removed = list.remove(0);
    MACRO_TEST_EQ(removed, true);
    return EXIT_SUCCESS;
}

int test_tree23_remove_all() {
    tree23<int> list;
    const int to_remove = 10;
    int i;
    for (i = 0; i < to_remove; ++i) {
        MACRO_TEST_CANT_EQ(list.add(), NULL);
    }
    int num_removed = list.remove_all();
    MACRO_TEST_EQ(num_removed, to_remove);
    return EXIT_SUCCESS;
}

int test_tree23_get() {
    tree23<int> list;
    const int to_get = 10;
    int i;
    for (i = 0; i < to_get; ++i) {
        MACRO_TEST_CANT_EQ(list.add(), NULL);
        MACRO_TEST_CANT_EQ(list.get(i), NULL);
    }
    return EXIT_SUCCESS;
}

int test_tree23_operator_subscript() {
    tree23<int> list;
    const int to_remove = 10;
    tree23_node<int> * added = (tree23_node<int> *)list.get_extend(to_remove);
    MACRO_TEST_CANT_EQ(added, NULL);
    tree23_node<int> * to_get = (tree23_node<int> *)list.get(to_remove);
    MACRO_TEST_POINTER_EQ(added, to_get);
    int num_removed = list.remove_all();
    // Add one because index 10 means 0 through 10 so 11 nodes
    MACRO_TEST_EQ(num_removed, to_remove + 1);
    return EXIT_SUCCESS;
}

int test_tree23_correct_data() {
    const int value = 42;
    tree23<int> root;
    root[0] = value;
    const int to_remove = 10;
    int i;
    for (i = 1; i < to_remove; ++i) {
        root[i] = i;
    }
    for (i = to_remove - 1; i > 0; --i) {
        MACRO_TEST_EQ(root[i], i);
    }
    MACRO_TEST_EQ(root[0], value);
    MACRO_TEST_EQ(root.remove_all(), to_remove);
    return EXIT_SUCCESS;
}

int test_tree23_operator_copy() {
    tree23<int> list;
    tree23<int> copy;
    const int to_remove = 10;
    // Create all the nodes in list
    list[to_remove] = 42;
    int added = list[to_remove];
    MACRO_TEST_EQ(added, 42);
    tree23_node<int> * to_get = (tree23_node<int> *)list.get(to_remove);
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
