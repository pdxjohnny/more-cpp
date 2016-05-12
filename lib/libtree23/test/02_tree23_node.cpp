/*
 * John Andersen
 * File: libtree23/test/tree23_node<int>.cpp
*/
#include "tree23.h"

int test_tree23_node_add() {
    tree23_node<int> root;
    tree23_node<int> * added = (tree23_node<int> *)root.add();
    MACRO_TEST_CANT_EQ(added, NULL);
    delete added;
    return EXIT_SUCCESS;
}

int test_tree23_node_remove_increasing() {
    tree23_node<int> root;
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

int test_tree23_node_remove_decreasing() {
    tree23_node<int> root;
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

int test_tree23_node_remove_all() {
    tree23_node<int> root;
    const int to_remove = 10;
    int i;
    for (i = 0; i < to_remove; ++i) {
        root.add();
    }
    MACRO_TEST_EQ(root.remove_all(), to_remove);
    return EXIT_SUCCESS;
}

int test_tree23_node_remove_self() {
    tree23_node_basic * root = new tree23_node<int>;
    MACRO_TEST_POINTER_EQ(root->remove_self(root), NULL);
    MACRO_TEST_POINTER_EQ(root, NULL);
    return EXIT_SUCCESS;
}

int test_tree23_node_get_index0() {
    tree23_node<int> root;
    MACRO_TEST_POINTER_EQ(root.get(0), &root);
    return EXIT_SUCCESS;
}

int test_tree23_node_get() {
    tree23_node<int> root;
    tree23_node<int> * a = (tree23_node<int> *)root.add();
    MACRO_TEST_POINTER_EQ(root.get(1), a);
    MACRO_TEST_EQ(root.remove_all(), 1);
    return EXIT_SUCCESS;
}

int test_tree23_node_correct_data() {
    const int value = 42;
    tree23_node<int> root;
    root.value() = value;
    const int to_remove = 10;
    int i;
    for (i = 0; i < to_remove; ++i) {
        ((tree23_node<int> *)root.add())->value() = i + 1;
    }
    for (i = to_remove; i > 0; --i) {
        MACRO_TEST_EQ(((tree23_node<int> *)root.get(i))->value(), i);
    }
    MACRO_TEST_EQ(root.value(), value);
    MACRO_TEST_EQ(root.remove_all(), to_remove);
    return EXIT_SUCCESS;
}
