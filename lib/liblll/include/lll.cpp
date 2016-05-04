#include "liblll.h"
#include <libmacro.h>

#ifndef LIBLLL_LLL
#define LIBLLL_LLL

// Constructor
template <typename data_type>
lll<data_type>::lll() {}

// Destructor
template <typename data_type>
lll<data_type>::~lll() {}

// Allows access by key value
template <typename data_type>
data_type & lll<data_type>::operator[](int index) {
    lll_node_basic * at_index = lll_basic::operator[](index);
    if (at_index == NULL) {
        MACRO_LOG_STR("at_index was null");
    }
    lll_node<data_type> * data_node = dynamic_cast<lll_node<data_type> *>(at_index);
    if (data_node == NULL) {
        MACRO_LOG_STR("data_node was null");
    }
    return data_node->value();
}

// Creates a node of the correct type
template <typename data_type>
bool lll<data_type>::create(lll_node_basic *& node) {
    node = new lll_node<data_type>;
    return (node != NULL);
}
#endif
