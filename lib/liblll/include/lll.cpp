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
data_type & lll<data_type>::operator[](unsigned int index) {
    return lll_basic::get_extend(index)->value();
}

// Return the value we are managing
template <typename data_type>
lll_node<data_type> *& lll<data_type>::head() {
    MACRO_LOG_STR("Correct head called");
    return head_value;
}
#endif
