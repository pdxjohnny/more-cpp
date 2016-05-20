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
data_type & lll<data_type>::operator[](int index) throw(lll_out_of_range) {
    lll_node_basic * at_index = lll_basic::operator[](index);
    if (at_index == NULL) {
        throw lll_out_of_range();
    }
    lll_node<data_type> * data_node = dynamic_cast<lll_node<data_type> *>(at_index);
    if (data_node == NULL) {
        throw lll_out_of_range();
    }
    return data_node->value();
}

// Creates a node of the correct type
template <typename data_type>
bool lll<data_type>::create(lll_node_basic *& node) {
    node = new lll_node<data_type>;
    return (node != NULL);
}

// Adds data to the lll
template <typename data_type>
lll<data_type> & lll<data_type>::operator+=(const data_type & add) {
    operator[](size()) = add;
    return *this;
}

// Displays the lll
template <typename data_type>
void lll<data_type>::display(std::ostream & out) {}

// Calls display
template <typename data_type>
std::ostream & operator << (std::ostream & out, lll<data_type> & list) {
    list.display(out);
    return out;
}

#endif
