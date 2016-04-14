/*
	Author: John Andersen
	Date: 02/19/2015
	Description: Binary Tree
*/
#include "libbst.h"

#ifndef BST_METHODS
#define BST_METHODS

/*
	Class: bst
	Method: Constructor
	Use: Initialises data members
	Input: None
	Output: None
*/
template <typename data_type>
bst<data_type>::bst()
{
	init();
}



/*
	Class: bst
	Method: Destructor
	Use: Deallocates all nodes
	Input: None
	Output: None
*/
template <typename data_type>
bst<data_type>::~bst()
{
	destroy();
}



/*
	Class: bst
	Method: init
	Use: Initialises data members
	Input: None
	Output: None
*/
template <typename data_type>
void bst<data_type>::init( void )
{
	root = NULL;
	in_bst = 0;
}



/*
	Class: bst
	Method: destroy
	Use: Deallocates all nodes
	Input: None
	Output: None
*/
template <typename data_type>
void bst<data_type>::destroy( void )
{
	destroy( root );
	in_bst = 0;
}



/*
	Class: bst
	Method: destroy
	Use: Deallocates all nodes recursivly
	Input: Root of bst
	Output: None
*/
template <typename data_type>
void bst<data_type>::destroy( bst_node<data_type> * & root )
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
	Class: bst
	Method: operator []
	Use: Access values as if the bst was a sorted array
	Input: Index of item
	Output: Value of node found
*/
template <typename data_type>
data_type & bst<data_type>::operator [] ( unsigned int num )
{
	return get( num );
}



/*
	Class: bst
	Method: operator []
	Use: Gets a key in the bst
	Input: Key to search for
	Output: Value of node found
*/
template <typename data_type>
data_type & bst<data_type>::operator [] ( char * key )
{
	return get( key );
}



/*
	Class: bst
	Method: key
	Use: Access keys as if the bst was a sorted array
	Input: Index of key
	Output: Key of node found
*/
template <typename data_type>
char * bst<data_type>::key( unsigned int num )
{
	// It cant be in the bst if its bigger than the number of item sin it
	if ( in_bst <= num )
	{
		return NULL;
	}
	unsigned int index = 0;
	return get( num, index, root )->key();
}



/*
	Class: bst
	Method: get
	Use: Access values as if the bst was a sorted array
	Input: Index of item
	Output: Value of node found
*/
template <typename data_type>
data_type & bst<data_type>::get( unsigned int num )
{
	// It wont be found so create it
	if ( in_bst <= num )
	{
		char key [20];
		sprintf( key, "%020d", num );
		return insert( key );
	}
	// Find it
	unsigned int index = 0;
	return get( num, index, root )->value();
}



/*
	Class: bst
	Method: get
	Use: Access nodes as if the bst was a sorted array
	Input: Index of item to find, current index, and root of the bst
	Output: Node found
*/
template <typename data_type>
bst_node<data_type> * bst<data_type>::get( unsigned int & num, unsigned int & index, bst_node<data_type> * root )
{
	if ( !root )
		return NULL;
	// To see if one of the sides found it
	bst_node<data_type> * found = NULL;
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
	Class: bst
	Method: get
	Use: Finds the value of a key in the bst
	Input: Key to search for
	Output: Value of node found
*/
template <typename data_type>
data_type & bst<data_type>::get( char * key )
{
    MACRO_PRINT_FILE_LINE("Looking for %s\n", key);
	// Try to get if that doesnt work then insert
	if ( !get( key, root ) )
	{
		return insert( key );
	}
	return get( key, root )->value();
}



/*
	Class: bst
	Method: get
	Use: Finds a node coresponding to a key in the bst
	Input: Key to search for and root of the bst
	Output: Node found
*/
template <typename data_type>
bst_node<data_type> * bst<data_type>::get( char * key, bst_node<data_type> * root )
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
	Class: bst
	Method: insert
	Use: Inserts a node into the bst
	Input: Key to insert
	Output: Values of the inserted node
*/
template <typename data_type>
data_type & bst<data_type>::insert( char * key )
{
	return insert( key, root )->value();
}



/*
	Class: bst
	Method: insert
	Use: Inserts a node into the bst
	Input: Key to insert
	Output: Values of the inserted node
*/
template <typename data_type>
bst_node<data_type> * bst<data_type>::insert_return_node( char * key )
{
	return insert( key, root );
}



/*
	Class: bst
	Method: insert_bst
	Use: Fixes problems with the red black tree to make sure it conforms to the rules
	Input: Key to insert and the root of the bst
	Output: Node inserted
*/
template <typename data_type>
bst_node<data_type> * bst<data_type>::insert( char * key, bst_node<data_type> * & root)
{
    // Save the node because fixing the tree may fuck it up
    bst_node<data_type> * node;

    // Insert like normal
    node = insert_bst(key, root);

    return node;
}



/*
	Class: bst
	Method: insert_bst
	Use: Inserts a node into the bst as if it was a bst
	Input: Key to insert and the root of the bst
	Output: Node inserted
*/
template <typename data_type>
bst_node<data_type> * bst<data_type>::insert_bst( char * key, bst_node<data_type> * & node)
{
    // Insert like normal
	if (!node)
	{
		return create_node(key, node);
	}
	// Binary search
    switch (search_bst(key, node)) {
    case BST_GO_LEFT:
        return insert_bst( key, node->left());
    case BST_GO_RIGHT:
        return insert_bst( key, node->right());
    }
    return NULL;
}



/*
	Class: bst
	Method: create_node
	Use: Inserts a node into the bst as if it was a bst
	Input: Key to insert and the root of the bst
	Output: Node inserted
*/
template <typename data_type>
bst_node<data_type> * bst<data_type>::create_node( char * key, bst_node<data_type> * & node)
{
    node_added();
    node = new bst_node<data_type>(key);
    return node;
}




/*
	Class: bst
	Method: node_added
	Use: Inserts a node into the bst as if it was a bst
	Input: Key to insert and the root of the bst
	Output: Node inserted
*/
template <typename data_type>
int bst<data_type>::node_added() {
    return ++in_bst;
}



/*
	Class: bst
	Method: insert_bst
	Use: Inserts a node into the bst as if it was a bst
	Input: Key to insert and the root of the bst
	Output: Node inserted
*/
template <typename data_type>
int bst<data_type>::search_bst( char * key, bst_node<data_type> * & node)
{
	// Binary search
	if ( 0 < strcmp( node->key(), key ) )
	{
        return BST_GO_LEFT;
	}
    return BST_GO_RIGHT;
}



/*
	Class: bst
	Method: contains
	Use: Checks if a key is in the bst
	Input: Key to search for
	Output: True or false that is set due to a not found being
		NULL and a found being the pointer so true
*/
template <typename data_type>
bool bst<data_type>::contains( char * key )
{
	return get( key, root );
}



/*
	Class: bst
	Method: size
	Use: How many items are in the bst
	Input: None
	Output: Number of nodes in the bst
*/
template <typename data_type>
unsigned int bst<data_type>::size( void )
{
	return in_bst;
}


/*
	Class: bst
	Method: all
	Use: Creates an array to access bst values
	Input: None
	Output: An array whos members a pointers to the values of nodes
		this allows a client to eficently opperate on the bst as if
		it were a sorted array without the need to find the thoretical
		position every time the subscript operator is used
*/
template <typename data_type>
data_type ** bst<data_type>::all( void )
{
	// More indexing, see get ( unsigned int num ) for explination of how this works
	unsigned int index = 0;
	data_type ** array = new data_type * [ in_bst ];
	all( index, array, root );
	return array;
}



/*
	Class: bst
	Method: all
	Use: Fills an array with the pointers to node values
	Input: Current index, array to fill, and pointer to root
	Output: None
*/
template <typename data_type>
void bst<data_type>::all( unsigned int & index , data_type ** array, bst_node<data_type> * root )
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
	Class: bst
	Method: keys
	Use: Creates an array to access bst keys
	Input: None
	Output: An array whos members a pointers to the keys of nodes
		this allows a client to eficently opperate on the bst as if
		it were a sorted array without the need to find the thoretical
		position every time the subscript operator is used
*/
template <typename data_type>
char ** bst<data_type>::keys( void )
{
	// More indexing, see get ( unsigned int num ) for explination of how this works
	unsigned int index = 0;
	char ** array = new char * [ in_bst ];
	keys( index, array, root );
	return array;
}



/*
	Class: bst
	Method: keys
	Use: Fills an array with the pointers to node keys
	Input: Current index, array to fill, and pointer to root
	Output: None
*/
template <typename data_type>
void bst<data_type>::keys( unsigned int & index , char ** array, bst_node<data_type> * root )
{
	// More indexing, see get ( unsigned int num ) for explination of how this works
	if ( !root )
		return;
	keys( index, array, root->left() );
	array[ index ] = root->key();
	++index;
	keys( index, array, root->right() );
	return;
}



/*
	Class: bst
	Method: remove
	Use: Removes a node from the bst
	Input: Key to remove
	Output: 1 for removed 0 for not	found
*/
template <typename data_type>
bool bst<data_type>::remove( char * key )
{
	return remove( key, root );
}



/*
	Class: bst
	Method: remove
	Use: Removes a node from the bst
	Input: Key of node to remove and root of bst
	Output: 1 for removed 0 for not	found
*/
template <typename data_type>
bool bst<data_type>::remove( char * key, bst_node<data_type> * & root )
{
	if ( !root )
	{
		return false;
	}
	if ( 0 == strcmp( root->key(), key ) )
	{
		// We know we are goiong to delete root
		bst_node<data_type> * del = root;
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
			bst_node<data_type> * successor = NULL;
			bst_node<data_type> * parent = NULL;
			// Find the inorder successor to the bst_node
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
		--in_bst;
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
	Class: bst
	Method: inorder
	Use: Finds the inorder successor to a node in the bst
	Input: The node whose inorder successor is being found
		and the node which will point to the parent of the successor 
	Output: The successor and the parent of the successor is also set
*/
template <typename data_type>
bst_node<data_type> * bst<data_type>::inorder( bst_node<data_type> * root, bst_node<data_type> * & parent )
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

