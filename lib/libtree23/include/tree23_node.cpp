#include "libtree23.h"
#include <libmacro.h>

#ifndef LIBTREE23_TREE23_NODE
#define LIBTREE23_TREE23_NODE

// Constructor
template <typename data_type>
tree23_node<data_type>::tree23_node() {}

// Destructor
template <typename data_type>
tree23_node<data_type>::~tree23_node() {}

// Copies the data of the node
template <typename data_type>
tree23_node_basic & tree23_node<data_type>::operator=(const tree23_node_basic & copy) {
    const tree23_node<data_type> * copy_ptr = dynamic_cast<const tree23_node<data_type> *>(&copy);
    this->data_value = copy_ptr->data_value;
    return *this;
}

// Creates a node of the correct type
template <typename data_type>
bool tree23_node<data_type>::create(tree23_node_basic *& node) {
    node = new tree23_node<data_type>;
    return (node != NULL);
}

// Return the value we are managing
template <typename data_type>
data_type & tree23_node<data_type>::value() {
    return data_value;
}
#endif
