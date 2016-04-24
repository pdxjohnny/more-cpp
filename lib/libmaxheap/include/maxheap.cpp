/*
	Author: John Andersen
	Date: 02/19/2015
	Description: Binary Tree
*/
#include "libmaxheap.h"

#ifndef MAXHEAP_METHODS
#define MAXHEAP_METHODS

/*
	Class: maxheap
	Method: Constructor
	Use: Initialises data members
	Input: None
	Output: None
*/
template <typename data_type>
maxheap<data_type>::maxheap() {}

/*
	Class: maxheap
	Method: Destructor
	Use: Purges data members
	Input: None
	Output: None
*/
template <typename data_type>
maxheap<data_type>::~maxheap() {}

/*
	Class: maxheap
	Method: insert_maxheap
	Use: Fixes problems with the red black tree to make sure it conforms to the rules
	Input: Key to insert and the root of the maxheap
	Output: Node inserted
*/
template <typename data_type>
bst_node<data_type> * maxheap<data_type>::insert( const char * key, bst_node<data_type> * & root)
{
    // Save the node because fixing the tree may fuck it up
    bst_node<data_type> * node;

    // Insert like normal
    node = insert_maxheap(key, root);

    // Fix the heap to make sure that the biggest is the root
    fix_maxheap(node);

    return node;
}

/*
	Class: maxheap
	Method: insert_maxheap
	Use: Inserts a node into the maxheap as if it was a maxheap
	Input: Key to insert and the root of the maxheap
	Output: Node inserted
*/
template <typename data_type>
bst_node<data_type> * maxheap<data_type>::fix_maxheap(bst_node<data_type> * & node)
{
    return NULL;
}

/*
	Class: maxheap
	Method: insert_maxheap
	Use: Inserts a node into the maxheap as if it was a maxheap
	Input: Key to insert and the root of the maxheap
	Output: Node inserted
*/
template <typename data_type>
int maxheap<data_type>::search_bst( const char * key, bst_node<data_type> * & node)
{
	// Binary search
	if ( 0 < strcmp( node->key(), key ) )
	{
        return BST_GO_LEFT;
	}
    return BST_GO_RIGHT;
}

#endif
