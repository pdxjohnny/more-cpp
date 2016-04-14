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
#ifndef BST
#define BST 1

#include <cstdio>
#include <cstdlib>
#include <cstring>

// For testing should return 42
int bst_test();

/*
    Struct: bst_node
    Use: Holds the left right and data for a key in the bst
*/
template <typename data_type>
class bst_node {
public:
    bst_node<data_type>();
    ~bst_node<data_type>();
    char *& key();
    data_type & value();
    bst_node *& left();
    bst_node *& right();
private:
    char * key_value;
    data_type data_value;
    bst_node * left_node;
    bst_node * right_node;
};


/*
    Class: bst
    Use: A binary bst organised by key
*/
template <typename data_type>
class bst
{
public:
    // Constructor and deconstructor
    bst<data_type>();
    ~bst<data_type>();
    // Allocates the bst
    void init( void );
    // Deallocates the bst
    void destroy( void );
    // Allows access by key value
    data_type & operator [] ( unsigned int num );
    data_type & operator [] ( char * key );
    // Access by index when ordered by key
    char * key( unsigned int num );
    data_type & get( unsigned int num );
    // Allows access by key value
    data_type & get( char * key );
    // Inserts a data of the bst type into the bst
    data_type & insert( char * key );
    // Check if key is present
    bool contains( char * key );
    // Returns the number of elements in the bst
    unsigned int size( void );
    // Returns the keys of the elements in the bst
    data_type ** all( void );
    char ** keys( void );
    // Removes an element from the array
    bool remove( char * key );
protected:
    // Deallocates the bst
    void destroy( bst_node<data_type> * & root );
    // Access by index when ordered by key
    bst_node<data_type> * get( unsigned int & num, unsigned int & index, bst_node<data_type> * root );
    // Allows access by key value
    bst_node<data_type> * get( char * key, bst_node<data_type> * root );
    // Inserts a data of the bst type into the bst
    bst_node<data_type> * insert_return_node( char * key );
    bst_node<data_type> * insert( char * key, bst_node<data_type> * & root );
    bst_node<data_type> * insert_bst( char * key, bst_node<data_type> * & root);
    void all( unsigned int & index , data_type ** array, bst_node<data_type> * root );
    // Returns the keys of the elements in the bst
    void keys( unsigned int & index , char ** array, bst_node<data_type> * root );
    bool remove( char * key, bst_node<data_type> * & root );
    bst_node<data_type> * inorder( bst_node<data_type> * root, bst_node<data_type> * & parent);
private:
    // Root of the bst
    bst_node<data_type> * root;
    // Number of nodes in the bst
    unsigned int in_bst;
};


#include "bst_node.cpp"
#include "bst.cpp"
#endif
