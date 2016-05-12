/*
 * John Andersen
 * File: libtree23/test/tree23_node_basic.cpp
*/
#include "tree23.h"

int test_tree23_basic_add() {
    tree23_basic list;
    MACRO_TEST_CANT_EQ(list.add(), NULL);
    return EXIT_SUCCESS;
}

int test_tree23_basic_remove() {
    tree23_basic list;
    MACRO_TEST_CANT_EQ(list.add(), NULL);
    bool removed = list.remove(0);
    MACRO_TEST_EQ(removed, true);
    return EXIT_SUCCESS;
}

int test_tree23_basic_remove_all() {
    tree23_basic list;
    const int to_remove = 10;
    int i;
    for (i = 0; i < to_remove; ++i) {
        MACRO_TEST_CANT_EQ(list.add(), NULL);
    }
    int num_removed = list.remove_all();
    MACRO_TEST_EQ(num_removed, to_remove);
    return EXIT_SUCCESS;
}

int test_tree23_basic_get() {
    tree23_basic list;
    tree23_node_basic * added = NULL;
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

int test_tree23_basic_operator_subscript() {
    tree23_basic list;
    const int to_remove = 10;
    tree23_node_basic * added = list[to_remove];
    MACRO_TEST_CANT_EQ(added, NULL);
    tree23_node_basic * to_get = list.get(to_remove);
    MACRO_TEST_POINTER_EQ(added, to_get);
    int num_removed = list.remove_all();
    // We need to add one to to_remove because index ten is
    // 0,1,2,3,4,5,6,7,8,9,10 so there are 11 numbers
    MACRO_TEST_EQ(num_removed, to_remove + 1);
    return EXIT_SUCCESS;
}

int test_tree23_basic_operator_copy() {
    tree23_basic list;
    tree23_basic copy;
    const int to_remove = 10;
    // Create all the nodes in list
    tree23_node_basic * added = list[to_remove];
    MACRO_TEST_CANT_EQ(added, NULL);
    tree23_node_basic * to_get = list.get(to_remove);
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
