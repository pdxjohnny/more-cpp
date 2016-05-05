#include "liblll.h"
#include <libmacro.h>

#ifndef LIBLLL_LLL_NODE
#define LIBLLL_LLL_NODE

// Constructor
template <typename data_type>
lll_node<data_type>::lll_node() {}

// Destructor
template <typename data_type>
lll_node<data_type>::~lll_node() {}

// Copies the data of the node
template <typename data_type>
lll_node_basic & lll_node<data_type>::operator=(const lll_node_basic & copy) {
    const lll_node<data_type> * copy_ptr = dynamic_cast<const lll_node<data_type> *>(&copy);
    this->data_value = copy_ptr->data_value;
    return *this;
}

// Creates a node of the correct type
template <typename data_type>
bool lll_node<data_type>::create(lll_node_basic *& node) {
    node = new lll_node<data_type>;
    return (node != NULL);
}

// Return the value we are managing
template <typename data_type>
data_type & lll_node<data_type>::value() {
    return data_value;
}
#endif
