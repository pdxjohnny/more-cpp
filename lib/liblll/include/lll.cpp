/*
	Author: John Andersen
	Date: 02/19/2015
	Description: Binary Tree
*/
#include "liblll.h"

#ifndef LLL_METHODS
#define LLL_METHODS

/*
	Class: lll
	Method: Constructor
	Use: Initialises data members
	Input: None
	Output: None
*/
template <typename data_type>
lll<data_type>::lll()
{
	init();
}



/*
	Class: lll
	Method: Destructor
	Use: Deallocates all nodes
	Input: None
	Output: None
*/
template <typename data_type>
lll<data_type>::~lll()
{
	destroy();
}



/*
	Class: lll
	Method: init
	Use: Initialises data members
	Input: None
	Output: None
*/
template <typename data_type>
void lll<data_type>::init( void )
{
	root = NULL;
	in_lll = 0;
}



/*
	Class: lll
	Method: destroy
	Use: Deallocates all nodes
	Input: None
	Output: None
*/
template <typename data_type>
void lll<data_type>::destroy( void )
{
	destroy( root );
	in_lll = 0;
}



/*
	Class: lll
	Method: destroy
	Use: Deallocates all nodes recursivly
	Input: Root of lll
	Output: None
*/
template <typename data_type>
void lll<data_type>::destroy( lll_node<data_type> * & root )
{
	if ( !root )
		return;
	// Go down booth sides
	destroy( root->left() );
	destroy( root->right() );
	// Delete the node
	delete root;
	// Set to to NULL
	root = NULL;
}



/*
	Class: lll
	Method: operator []
	Use: Access values as if the lll was a sorted array
	Input: Index of item
	Output: Value of node found
*/
template <typename data_type>
data_type & lll<data_type>::operator [] ( unsigned int num )
{
	return get( num );
}



/*
	Class: lll
	Method: operator []
	Use: Gets a key in the lll
	Input: Key to search for
	Output: Value of node found
*/
template <typename data_type>
data_type & lll<data_type>::operator [] ( const char * key )
{
	return get( key );
}



/*
	Class: lll
	Method: key
	Use: Access keys as if the lll was a sorted array
	Input: Index of key
	Output: Key of node found
*/
template <typename data_type>
char * lll<data_type>::key( unsigned int num )
{
	// It cant be in the lll if its bigger than the number of item sin it
	if ( in_lll <= num )
	{
		return NULL;
	}
	unsigned int index = 0;
	return get( num, index, root )->key();
}



/*
	Class: lll
	Method: get
	Use: Access values as if the lll was a sorted array
	Input: Index of item
	Output: Value of node found
*/
template <typename data_type>
data_type & lll<data_type>::get( unsigned int num )
{
	// It wont be found so create it
	if ( in_lll <= num )
	{
		char key [20];
		sprintf( key, "%020d", num );
		return this->insert( key );
	}
	// Find it
	unsigned int index = 0;
	return get( num, index, root )->value();
}



/*
	Class: lll
	Method: get
	Use: Access nodes as if the lll was a sorted array
	Input: Index of item to find, current index, and root of the lll
	Output: Node found
*/
template <typename data_type>
lll_node<data_type> * lll<data_type>::get( unsigned int & num, unsigned int & index, lll_node<data_type> * root )
{
	if ( !root )
		return NULL;
	// To see if one of the sides found it
	lll_node<data_type> * found = NULL;
	// Look of the index on the left, that will be index 0 if its the leftmost node
	found = get( num, index, root->left() );
	if ( found )
	{
		return found;
	}
	// Check if this node is the index
	if ( num == index )
	{
		return root;
	}
	// increment the index
	++index;
	// Look of the index on the right
	found = get( num, index, root->right() );
	if ( found )
	{
		return found;
	}
	return NULL;
}



/*
	Class: lll
	Method: get
	Use: Finds the value of a key in the lll
	Input: Key to search for
	Output: Value of node found
*/
template <typename data_type>
data_type & lll<data_type>::get( const char * key )
{
	// Try to get if that doesnt work then insert
	if ( !get( key, root ) )
	{
		return this->insert( key );
	}
	return get( key, root )->value();
}



/*
	Class: lll
	Method: get
	Use: Finds a node coresponding to a key in the lll
	Input: Key to search for and root of the lll
	Output: Node found
*/
template <typename data_type>
lll_node<data_type> * lll<data_type>::get( const char * key, lll_node<data_type> * root )
{
	// Look for the key this si a simple binary search algoritham
	if ( !root )
	{
		return NULL;
	}
	// If key return
	if ( 0 == strcmp( root->key(), key ) )
	{
		return root;
	}
	// If less go left
	else if ( 0 < strcmp( root->key(), key ) )
	{
		return get( key, root->left() );
	}
	// If greater than or equal to go right
	return get( key, root->right() );
}



/*
	Class: lll
	Method: insert
	Use: Inserts a node into the lll
	Input: Key to insert
	Output: Values of the inserted node
*/
template <typename data_type>
data_type & lll<data_type>::insert( const char * key )
{
	return this->insert( key, root )->value();
}



/*
	Class: lll
	Method: insert
	Use: Inserts a node into the lll
	Input: Key to insert
	Output: Values of the inserted node
*/
template <typename data_type>
lll_node<data_type> * lll<data_type>::insert_return_node( const char * key )
{
	return this->insert( key, root );
}



/*
	Class: lll
	Method: insert_lll
	Use: Fixes problems with the red black tree to make sure it conforms to the rules
	Input: Key to insert and the root of the lll
	Output: Node inserted
*/
template <typename data_type>
lll_node<data_type> * lll<data_type>::insert( const char * key, lll_node<data_type> * & root)
{
    // Save the node because fixing the tree may fuck it up
    lll_node<data_type> * node;

    // Insert like normal
    node = this->insert_lll(key, root);

    return node;
}



/*
	Class: lll
	Method: insert_lll
	Use: Inserts a node into the lll as if it was a lll
	Input: Key to insert and the root of the lll
	Output: Node inserted
*/
template <typename data_type>
lll_node<data_type> * lll<data_type>::insert_lll( const char * key, lll_node<data_type> * & node)
{
    // Insert like normal
	if (!node)
	{
		return create_node(key, node);
	}
	// Binary search
    switch (search_lll(key, node)) {
    case LLL_GO_LEFT:
        return this->insert_lll( key, node->left());
    case LLL_GO_RIGHT:
        return this->insert_lll( key, node->right());
    }
    return NULL;
}



/*
	Class: lll
	Method: create_node
	Use: Inserts a node into the lll as if it was a lll
	Input: Key to insert and the root of the lll
	Output: Node inserted
*/
template <typename data_type>
lll_node<data_type> * lll<data_type>::create_node( const char * key, lll_node<data_type> * & node)
{
    node_added();
    node = new lll_node<data_type>(key);
    return node;
}




/*
	Class: lll
	Method: node_added
	Use: Inserts a node into the lll as if it was a lll
	Input: Key to insert and the root of the lll
	Output: Node inserted
*/
template <typename data_type>
int lll<data_type>::node_added() {
    return ++in_lll;
}



/*
	Class: lll
	Method: insert_lll
	Use: Inserts a node into the lll as if it was a lll
	Input: Key to insert and the root of the lll
	Output: Node inserted
*/
template <typename data_type>
int lll<data_type>::search_lll( const char * key, lll_node<data_type> * & node)
{
	// Binary search
	if ( 0 < strcmp( node->key(), key ) )
	{
        return LLL_GO_LEFT;
	}
    return LLL_GO_RIGHT;
}



/*
	Class: lll
	Method: contains
	Use: Checks if a key is in the lll
	Input: Key to search for
	Output: True or false that is set due to a not found being
		NULL and a found being the pointer so true
*/
template <typename data_type>
bool lll<data_type>::contains( const char * key )
{
	return get( key, root );
}



/*
	Class: lll
	Method: size
	Use: How many items are in the lll
	Input: None
	Output: Number of nodes in the lll
*/
template <typename data_type>
unsigned int lll<data_type>::size( void )
{
	return in_lll;
}


/*
	Class: lll
	Method: all
	Use: Creates an array to access lll values
	Input: None
	Output: An array whos members a pointers to the values of nodes
		this allows a client to eficently opperate on the lll as if
		it were a sorted array without the need to find the thoretical
		position every time the subscript operator is used
*/
template <typename data_type>
data_type ** lll<data_type>::all( void )
{
	// More indexing, see get ( unsigned int num ) for explination of how this works
	unsigned int index = 0;
	data_type ** array = new data_type * [ in_lll ];
	all( index, array, root );
	return array;
}



/*
	Class: lll
	Method: all
	Use: Fills an array with the pointers to node values
	Input: Current index, array to fill, and pointer to root
	Output: None
*/
template <typename data_type>
void lll<data_type>::all( unsigned int & index , data_type ** array, lll_node<data_type> * root )
{
	// More indexing, see get ( unsigned int num ) for explination of how this works
	if ( !root )
		return;
	all( index, array, root->left() );
	array[ index ] = & root->value();
	++index;
	all( index, array, root->right() );
	return;
}



/*
	Class: lll
	Method: keys
	Use: Creates an array to access lll keys
	Input: None
	Output: An array whos members a pointers to the keys of nodes
		this allows a client to eficently opperate on the lll as if
		it were a sorted array without the need to find the thoretical
		position every time the subscript operator is used
*/
template <typename data_type>
char *** lll<data_type>::keys( void )
{
	// More indexing, see get ( unsigned int num ) for explination of how this works
	unsigned int index = 0;
	char *** array = new char ** [in_lll + 1];
	keys( index, array, root );
    array[in_lll] = NULL;
	return array;
}



/*
	Class: lll
	Method: keys
	Use: Fills an array with the pointers to node keys
	Input: Current index, array to fill, and pointer to root
	Output: None
*/
template <typename data_type>
void lll<data_type>::keys( unsigned int & index , char *** array, lll_node<data_type> * root )
{
	// More indexing, see get ( unsigned int num ) for explination of how this works
	if ( !root ) {
		return;
    }
	keys( index, array, root->left() );
    char ** key_copy_ptr = new char *;
    char * key_copy = new char [strlen(root->key()) + 1];
    strcpy(key_copy, root->key());
    *key_copy_ptr = key_copy;
	array[index] = key_copy_ptr;
	++index;
	keys( index, array, root->right() );
	return;
}



/*
	Class: lll
	Method: remove
	Use: Removes a node from the lll
	Input: Key to remove
	Output: 1 for removed 0 for not	found
*/
template <typename data_type>
bool lll<data_type>::remove( const char * key )
{
	return remove( key, root );
}



/*
	Class: lll
	Method: remove
	Use: Removes a node from the lll
	Input: Key of node to remove and root of lll
	Output: 1 for removed 0 for not	found
*/
template <typename data_type>
bool lll<data_type>::remove( const char * key, lll_node<data_type> * & root )
{
	if ( !root )
	{
		return false;
	}
	if ( 0 == strcmp( root->key(), key ) )
	{
		// We know we are goiong to delete root
		lll_node<data_type> * del = root;
		// If its a leaf then no problem delete
		if ( !root->left() && !root->right() )
		{
			root = NULL;
		}
		// If it has a left and not a right just replace
		else if ( root->left() && !root->right() )
		{
			root = root->left();
		}
		// If it has a right and not a left just replace
		else if ( root->right() && !root->left() )
		{
			root = root->right();
		}
		// If it has two children
		else
		{
			// Find inorder successor
			lll_node<data_type> * successor = NULL;
			lll_node<data_type> * parent = NULL;
			// Find the inorder successor to the lll_node
			successor = inorder( root, parent );
			// Set the left of the parent of the inorder
			// to the inorder's right, it will have no left
			// if it did then it wouldn't be the inorder
			successor->left() = root->left();
			if ( parent )
				parent->left() = successor->right();
			// Make suer we arent seting the right to ourself
			if ( parent && parent->right() != root->right() )
				successor->right() = root->right();
			root = successor;
		}
		// Delete
		delete del;
		--in_lll;
		return true;
	}
	// Binary search
	else if ( 0 < strcmp( root->key(), key ) )
	{
		return remove( key, root->left() );
	}
	return remove( key, root->right() );
}



/*
	Class: lll
	Method: inorder
	Use: Finds the inorder successor to a node in the lll
	Input: The node whose inorder successor is being found
		and the node which will point to the parent of the successor 
	Output: The successor and the parent of the successor is also set
*/
template <typename data_type>
lll_node<data_type> * lll<data_type>::inorder( lll_node<data_type> * root, lll_node<data_type> * & parent )
{
	// Goes right then all the way left and returns
	if ( !root )
	{
		return NULL;
	}
	if ( root->right() )
	{
		parent = root;
		root = root->right();
	}
	while ( root->left() )
	{
		parent = root;
		root = root->left();
	}
	return root;
}

#endif

