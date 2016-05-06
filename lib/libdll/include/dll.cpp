#include "libdll.h"
#include <libmacro.h>

#ifndef LIBDLL_DLL
#define LIBDLL_DLL

// Constructor
template <typename data_type>
dll<data_type>::dll() {}

// Destructor
template <typename data_type>
dll<data_type>::~dll() {}

// Allows access by key value
template <typename data_type>
data_type & dll<data_type>::operator[](int index) throw(dll_out_of_range) {
    dll_node_basic * at_index = dll_basic::operator[](index);
    if (at_index == NULL) {
        throw dll_out_of_range();
    }
    dll_node<data_type> * data_node = dynamic_cast<dll_node<data_type> *>(at_index);
    if (data_node == NULL) {
        throw dll_out_of_range();
    }
    return data_node->value();
}

// Creates a node of the correct type
template <typename data_type>
bool dll<data_type>::create(dll_node_basic *& node) {
    node = new dll_node<data_type>;
    return (node != NULL);
}
#endif
