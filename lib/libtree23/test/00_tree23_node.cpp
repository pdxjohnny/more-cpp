/*
 * John Andersen
 * File: libtree23/test/tree23_node_basic.cpp
*/
#include "tree23.h"

int test_tree23_node_create() {
    tree23_node<int> root;
    int data = 5;
    int i;
    for (i = 999; i >= 0; --i) {
        root.add(data);
    }
    root.remove_all();
    return EXIT_SUCCESS;
}
