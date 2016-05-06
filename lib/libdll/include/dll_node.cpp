#include "libdll.h"
#include <libmacro.h>

#ifndef LIBDLL_DLL_NODE
#define LIBDLL_DLL_NODE

// Constructor
template <typename data_type>
dll_node<data_type>::dll_node() {}

// Destructor
template <typename data_type>
dll_node<data_type>::~dll_node() {}

// Copies the data of the node
template <typename data_type>
dll_node_basic & dll_node<data_type>::operator=(const dll_node_basic & copy) {
    const dll_node<data_type> * copy_ptr = dynamic_cast<const dll_node<data_type> *>(&copy);
    this->data_value = copy_ptr->data_value;
    return *this;
}

// Creates a node of the correct type
template <typename data_type>
bool dll_node<data_type>::create(dll_node_basic *& node) {
    node = new dll_node<data_type>;
    return (node != NULL);
}

// Return the value we are managing
template <typename data_type>
data_type & dll_node<data_type>::value() {
    return data_value;
}
#endif
