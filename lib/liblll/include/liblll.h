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
#ifndef LLL
#define LLL 1
#define LLL_GO_LEFT 1
#define LLL_GO_RIGHT 2

#include <cstdio>
#include <cstdlib>
#include <cstring>

/*
    Struct: lll_node
    Use: Holds the left right and data for a key in the lll
*/
template <typename data_type>
class lll_node {
public:
    lll_node<data_type>();
    lll_node<data_type>( const char * key );
    ~lll_node<data_type>();
    char *& key();
    data_type & value();
    lll_node *& left();
    lll_node *& right();
private:
    char * key_value;
    data_type data_value;
    lll_node * left_node;
    lll_node * right_node;
};


/*
    Class: lll
    Use: A binary lll organised by key
*/
template <typename data_type>
class lll
{
public:
    // Constructor and deconstructor
    lll<data_type>();
    ~lll<data_type>();
    // Allocates the lll
    void init( void );
    // Deallocates the lll
    void destroy( void );
    // Allows access by key value
    data_type & operator [] ( unsigned int num );
    data_type & operator [] ( const char * key );
    // Access by index when ordered by key
    char * key( unsigned int num );
    data_type & get( unsigned int num );
    // Allows access by key value
    data_type & get( const char * key );
    // Inserts a data of the lll type into the lll
    virtual data_type & insert( const char * key );
    // Check if key is present
    bool contains( const char * key );
    // Returns the number of elements in the lll
    unsigned int size( void );
    // Returns the keys of the elements in the lll
    data_type ** all( void );
    char *** keys( void );
    // Removes an element from the array
    bool remove( const char * key );
protected:
    // Deallocates the lll
    void destroy( lll_node<data_type> * & root );
    // Access by index when ordered by key
    lll_node<data_type> * get( unsigned int & num, unsigned int & index, lll_node<data_type> * root );
    // Allows access by key value
    lll_node<data_type> * get( const char * key, lll_node<data_type> * root );
    // Inserts a data of the lll type into the lll
    lll_node<data_type> * insert_return_node( const char * key );
    lll_node<data_type> * insert( const char * key, lll_node<data_type> * & root );
    lll_node<data_type> * insert_lll( const char * key, lll_node<data_type> * & root);
    virtual lll_node<data_type> * create_node( const char * key, lll_node<data_type> * & root);
    int node_added();
    virtual int search_lll( const char * key, lll_node<data_type> * & root);
    void all( unsigned int & index , data_type ** array, lll_node<data_type> * root );
    // Returns the keys of the elements in the lll
    void keys( unsigned int & index , char *** array, lll_node<data_type> * root );
    bool remove( const char * key, lll_node<data_type> * & root );
    lll_node<data_type> * inorder( lll_node<data_type> * root, lll_node<data_type> * & parent);
private:
    // Root of the lll
    lll_node<data_type> * root;
    // Number of nodes in the lll
    unsigned int in_lll;
};


#include "lll_node.cpp"
#include "lll.cpp"
#endif
