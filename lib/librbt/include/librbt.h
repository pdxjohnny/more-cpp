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
#ifndef RBT
#define RBT 1
#define RBT_BLACK 1
#define RBT_RED 2

#include <cstdio>
#include <cstdlib>
#include <cstring>

// For testing should return 42
int rbt_test();

/*
	Struct: rbt_node
	Use: Holds the left right and data for a key in the rbt
*/
template <typename data_type>
struct rbt_node
{
    char color;
	char * key;
	data_type value;
	rbt_node * up;
	rbt_node * left;
	rbt_node * right;
};


/*
	Class: rbt
	Use: A binary rbt organised by key
*/
template <typename data_type>
class rbt
{
public:
	// Constructor and deconstructor
	rbt<data_type>();
	~rbt<data_type>();
	// Allocates the rbt
	void init( void );
	// Deallocates the rbt
	void destroy( void );
	void destroy( rbt_node<data_type> * & root );
	// Allows access by key value
	data_type & operator [] ( unsigned int num );
	data_type & operator [] ( char * key );
	// Access by index when ordered by key
	char * key( unsigned int num );
	data_type & get( unsigned int num );
	rbt_node<data_type> * get( unsigned int & num, unsigned int & index, rbt_node<data_type> * root );
	// Allows access by key value
	data_type & get( char * key );
	rbt_node<data_type> * get( char * key, rbt_node<data_type> * root );
	// Inserts a data of the rbt type into the rbt
	data_type & insert( char * key );
    rbt_node<data_type> * insert_return_node( char * key );
	rbt_node<data_type> * insert( char * key, rbt_node<data_type> * & root );
	rbt_node<data_type> * insert_bst( char * key, rbt_node<data_type> * & root, rbt_node<data_type> * & above);
	rbt_node<data_type> * insert_rbt(rbt_node<data_type> * & node);
    void rotate_left(rbt_node<data_type> *);
    void rotate_right(rbt_node<data_type> *);
	// Check if key is present
	bool contains( char * key );
	// Returns the number of elements in the rbt
	unsigned int size( void );
	// Returns the keys of the elements in the rbt
	data_type ** all( void );
	void all( unsigned int & index , data_type ** array, rbt_node<data_type> * root );
	// Returns the keys of the elements in the rbt
	char ** keys( void );
	void keys( unsigned int & index , char ** array, rbt_node<data_type> * root );
	// Removes an element from the array
	bool remove( char * key );
	bool remove( char * key, rbt_node<data_type> * & root );
	rbt_node<data_type> * inorder( rbt_node<data_type> * root, rbt_node<data_type> * & parent );
private:
	// Root of the rbt
	rbt_node<data_type> * root;
	// Number of nodes in the rbt
	unsigned int in_rbt;
};


#include "rbt.cpp"
#endif
