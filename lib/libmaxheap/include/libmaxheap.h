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
#define MAXHEAP_GO_LEFT 1
#define MAXHEAP_GO_RIGHT 2

#include <cstdio>
#include <cstdlib>
#include <cstring>

#include <libmacro.h>

// For testing should return 42
int maxheap_test();

/*
    Struct: maxheap_node
    Use: Holds the left right and data for a key in the maxheap
*/
template <typename data_type>
class maxheap_node {
public:
    maxheap_node<data_type>();
    maxheap_node<data_type>( const char * key );
    ~maxheap_node<data_type>();
    char *& key();
    data_type & value();
    maxheap_node *& left();
    maxheap_node *& right();
private:
    char * key_value;
    data_type data_value;
    maxheap_node * left_node;
    maxheap_node * right_node;
};


/*
    Class: maxheap
    Use: A binary maxheap organised by key
*/
template <typename data_type>
class maxheap
{
public:
    // Constructor and deconstructor
    maxheap<data_type>();
    ~maxheap<data_type>();
    // Allocates the maxheap
    void init( void );
    // Deallocates the maxheap
    void destroy( void );
    // Allows access by key value
    data_type & operator [] ( unsigned int num );
    data_type & operator [] ( const char * key );
    // Access by index when ordered by key
    char * key( unsigned int num );
    data_type & get( unsigned int num );
    // Allows access by key value
    data_type & get( const char * key );
    // Inserts a data of the maxheap type into the maxheap
    virtual data_type & insert( const char * key );
    // Check if key is present
    bool contains( const char * key );
    // Returns the number of elements in the maxheap
    unsigned int size( void );
    // Returns the keys of the elements in the maxheap
    data_type ** all( void );
    char *** keys( void );
    // Removes an element from the array
    bool remove( const char * key );
protected:
    // Deallocates the maxheap
    void destroy( maxheap_node<data_type> * & root );
    // Access by index when ordered by key
    maxheap_node<data_type> * get( unsigned int & num, unsigned int & index, maxheap_node<data_type> * root );
    // Allows access by key value
    maxheap_node<data_type> * get( const char * key, maxheap_node<data_type> * root );
    // Inserts a data of the maxheap type into the maxheap
    maxheap_node<data_type> * insert_return_node( const char * key );
    maxheap_node<data_type> * insert( const char * key, maxheap_node<data_type> * & root );
    maxheap_node<data_type> * insert_bst( const char * key, maxheap_node<data_type> * & root);
    maxheap_node<data_type> * fix_maxheap( maxheap_node<data_type> * & root );
    virtual maxheap_node<data_type> * create_node( const char * key, maxheap_node<data_type> * & root);
    int node_added();
    virtual int search_maxheap( const char * key, maxheap_node<data_type> * & root);
    void all( unsigned int & index , data_type ** array, maxheap_node<data_type> * root );
    // Returns the keys of the elements in the maxheap
    void keys( unsigned int & index , char *** array, maxheap_node<data_type> * root );
    bool remove( const char * key, maxheap_node<data_type> * & root );
    maxheap_node<data_type> * inorder( maxheap_node<data_type> * root, maxheap_node<data_type> * & parent);
private:
    // Root of the maxheap
    maxheap_node<data_type> * root;
    // Number of nodes in the maxheap
    unsigned int in_maxheap;
};


#include "maxheap_node.cpp"
#include "maxheap.cpp"
#endif
