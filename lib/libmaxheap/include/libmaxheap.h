/*
    Author: John Andersen
    Date: 04/07/2015
    Description: Red Black Tree
*/



// For NULL
#ifndef NULL
    #define NULL 0
#endif

// Ensure nothing gets redeclared
#ifndef MAXHEAP
#define MAXHEAP 1

#include <cstdio>
#include <cstdlib>
#include <cstring>

#include <libbst.h>

// For testing should return 42
int maxheap_test();

/*
    Class: maxheap
    Use: A binary maxheap organised by key
*/
template <typename data_type>
class maxheap : public bst<data_type>
{
public:
    // Constructor and deconstructor
    maxheap<data_type>();
    ~maxheap<data_type>();
protected:
    bst_node<data_type> * insert( const char * key, bst_node<data_type> * & root );
    virtual int search_bst( const char * key, bst_node<data_type> * & root);
    bst_node<data_type> * fix_maxheap( bst_node<data_type> * & root );
};


#include "maxheap.cpp"
#endif
