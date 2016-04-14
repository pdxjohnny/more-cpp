#include "libbst.h"

#ifndef BST_NODE_METHODS
#define BST_NODE_METHODS

template <typename data_type>
bst_node<data_type>::bst_node() : key_value(NULL), left_node(NULL), right_node(NULL) {}

template <typename data_type>
bst_node<data_type>::~bst_node() {
}

template <typename data_type>
char *& bst_node<data_type>::key() {
    return key_value;
}

template <typename data_type>
data_type & bst_node<data_type>::value() {
    return data_value;
}

template <typename data_type>
bst_node<data_type> *& bst_node<data_type>::left() {
    return left_node;
}

template <typename data_type>
bst_node<data_type> *& bst_node<data_type>::right() {
    return right_node;
}

#endif

