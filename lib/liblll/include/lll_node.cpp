#include "liblll.h"

#ifndef LIBLLL_LLL_NODE
#define LIBLLL_LLL_NODE

// Constructor
template <typename data_type>
lll_node<data_type>::lll_node() {}

// Destructor
template <typename data_type>
lll_node<data_type>::~lll_node() {}

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
