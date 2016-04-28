/*
 * John Andersen
 * File: liblll/include/lll.cpp
*/

#include "liblll.h"

#ifndef LLL_NODE_METHODS
#define LLL_NODE_METHODS

template <typename data_type>
lll_node<data_type>::lll_node() : key_value(NULL), left_node(NULL), right_node(NULL) {}

template <typename data_type>
lll_node<data_type>::lll_node( const char * key ) : left_node(NULL), right_node(NULL) {
    // Allocate the key
    key_value = new char [strlen( key ) + 1];
    strcpy(key_value, key);
}

template <typename data_type>
lll_node<data_type>::~lll_node() {
    if (key_value != NULL) {
        delete[] key_value;
    }
}

template <typename data_type>
char *& lll_node<data_type>::key() {
    return key_value;
}

template <typename data_type>
data_type & lll_node<data_type>::value() {
    return data_value;
}

template <typename data_type>
lll_node<data_type> *& lll_node<data_type>::left() {
    return left_node;
}

template <typename data_type>
lll_node<data_type> *& lll_node<data_type>::right() {
    return right_node;
}

#endif

