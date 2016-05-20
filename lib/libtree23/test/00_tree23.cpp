/*
 * John Andersen
 * File: libtree23/test/tree23_basic.cpp
*/
#include "tree23.h"
const int count = 4;

int test_tree23_create() {
    tree23<int> root;
    int i;
    for (i = count; i >= 0; --i) {
        root.add(i);
    }
    root.remove_all();
    return EXIT_SUCCESS;
}

int test_tree23_order() {
    tree23<int> root;
    int i;
    for (i = count; i >= 0; --i) {
        root.add(i);
    }
    int val;
    try {
        for (i = count; i >= 0; --i) {
            val = root[i];
            MACRO_TEST_EQ(val, i);
        }
    } catch (tree23_out_of_range err) {
        root.remove_all();
        errno = -1;
        MACRO_LOG_FATAL("ERROR: %s", err.what());
    }
    root.remove_all();
    return EXIT_SUCCESS;
}

int test_tree23_copy() {
    tree23<int> root;
    tree23<int> copy;
    int i;
    for (i = count; i >= 0; --i) {
        root += i;
    }
    copy = root;
    int val;
    try {
        for (i = count; i >= 0; --i) {
            val = copy[i];
            MACRO_TEST_EQ(val, i);
            MACRO_TEST_EQ(root[i], copy[i]);
        }
    } catch (tree23_out_of_range err) {
        root.remove_all();
        copy.remove_all();
        errno = -1;
        MACRO_LOG_FATAL("ERROR: index %d: %s", i, err.what());
    }
    root.remove_all();
    copy.remove_all();
    return EXIT_SUCCESS;
}
