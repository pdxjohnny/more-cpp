#include "libtree23.h"
#include <libmacro.h>

#ifndef LIBTREE23_TREE23
#define LIBTREE23_TREE23

// Constructor
template <typename data_type>
tree23<data_type>::tree23() {}

// Destructor
template <typename data_type>
tree23<data_type>::~tree23() {}

// Allows access by key value
template <typename data_type>
data_type & tree23<data_type>::operator[](const char * key) throw(tree23_out_of_range) {
    tree23_node_basic * at_index = tree23_basic::operator[](index);
    if (at_index == NULL) {
        throw tree23_out_of_range();
    }
    tree23_node<data_type> * data_node = dynamic_cast<tree23_node<data_type> *>(at_index);
    if (data_node == NULL) {
        throw tree23_out_of_range();
    }
    return data_node->value();
}

// Creates a node of the correct type
template <typename data_type>
bool tree23<data_type>::create(tree23_node_basic *& node) {
    node = new tree23_node<data_type>;
    return (node != NULL);
}
#endif
