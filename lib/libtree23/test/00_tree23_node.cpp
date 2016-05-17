/*
 * John Andersen
 * File: libtree23/test/tree23_node_basic.cpp
*/
#include "tree23.h"

class comparable {
};

int test_tree23_node_create() {
    tree23_node<comparable> root;
    return EXIT_SUCCESS;
}
