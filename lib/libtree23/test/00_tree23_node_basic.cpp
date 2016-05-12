/*
 * John Andersen
 * File: libtree23/test/tree23_node_basic.cpp
*/
#include "tree23.h"

#define lnb tree23_node_basic

int test_tree23_node_basic_add() {
    lnb root;
    lnb * added = root.add();
    MACRO_TEST_CANT_EQ(added, NULL);
    delete added;
    return EXIT_SUCCESS;
}

int test_tree23_node_basic_remove_increasing() {
    lnb root;
    const int to_remove = 10;
    int i;
    for (i = 0; i < to_remove; ++i) {
        MACRO_TEST_CANT_EQ(root.add(), NULL);
    }
    for (i = 1; i <= to_remove; ++i) {
        MACRO_TEST_EQ(root.remove(1), true);
    }
    return EXIT_SUCCESS;
}

int test_tree23_node_basic_remove_decreasing() {
    lnb root;
    const int to_remove = 10;
    int i;
    for (i = 0; i < to_remove; ++i) {
        MACRO_TEST_CANT_EQ(root.add(), NULL);
    }
    for (i = to_remove; i > 0; --i) {
        MACRO_TEST_EQ(root.remove(i), true);
    }
    return EXIT_SUCCESS;
}

int test_tree23_node_basic_remove_all() {
    lnb root;
    const int to_remove = 10;
    int i;
    for (i = 0; i < to_remove; ++i) {
        root.add();
    }
    MACRO_TEST_EQ(root.remove_all(), to_remove);
    return EXIT_SUCCESS;
}

int test_tree23_node_basic_remove_self() {
    lnb * root = new lnb;
    MACRO_TEST_POINTER_EQ(root->remove_self(root), NULL);
    MACRO_TEST_POINTER_EQ(root, NULL);
    return EXIT_SUCCESS;
}

int test_tree23_node_basic_get_index0() {
    lnb root;
    MACRO_TEST_POINTER_EQ(root.get(0), &root);
    return EXIT_SUCCESS;
}

int test_tree23_node_basic_get() {
    lnb root;
    lnb * added = NULL;
    const int to_get = 10;
    int i;
    for (i = 1; i < to_get + 1; ++i) {
        added = root.add();
        MACRO_TEST_CANT_EQ(added, NULL);
        MACRO_TEST_CANT_EQ(root.get(i), NULL);
        MACRO_TEST_POINTER_EQ(root.get(i), added);
    }
    int num_removed = root.remove_all();
    MACRO_TEST_EQ(num_removed, to_get);
    return EXIT_SUCCESS;
}

int test_tree23_node_basic_copy() {
    lnb root;
    lnb copy;
    lnb * added = NULL;
    const int to_get = 10;
    int i;
    for (i = 1; i < to_get + 1; ++i) {
        added = root.add();
        MACRO_TEST_CANT_EQ(added, NULL);
        MACRO_TEST_CANT_EQ(root.get(i), NULL);
        MACRO_TEST_POINTER_EQ(root.get(i), added);
    }
    // Now preform the copy
    copy.copy(root);
    int num_removed = root.remove_all();
    MACRO_TEST_EQ(num_removed, to_get);
    num_removed = copy.remove_all();
    MACRO_TEST_EQ(num_removed, to_get);
    return EXIT_SUCCESS;
}
