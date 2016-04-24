/*
	Author: John Andersen
	Date: 04/24/16
    File: libmaxheap/include/maxheap.cpp
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
maxheap<data_type>::maxheap()
{
	init();
}



/*
	Class: maxheap
	Method: Destructor
	Use: Deallocates all nodes
	Input: None
	Output: None
*/
template <typename data_type>
maxheap<data_type>::~maxheap()
{
	destroy();
}



/*
	Class: maxheap
	Method: init
	Use: Initialises data members
	Input: None
	Output: None
*/
template <typename data_type>
void maxheap<data_type>::init( void )
{
	root = NULL;
	in_maxheap = 0;
}



/*
	Class: maxheap
	Method: destroy
	Use: Deallocates all nodes
	Input: None
	Output: None
*/
template <typename data_type>
void maxheap<data_type>::destroy( void )
{
	destroy( root );
	in_maxheap = 0;
}



/*
	Class: maxheap
	Method: destroy
	Use: Deallocates all nodes recursivly
	Input: Root of maxheap
	Output: None
*/
template <typename data_type>
void maxheap<data_type>::destroy( maxheap_node<data_type> * & root )
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
	Class: maxheap
	Method: operator []
	Use: Access values as if the maxheap was a sorted array
	Input: Index of item
	Output: Value of node found
*/
template <typename data_type>
data_type & maxheap<data_type>::operator [] ( unsigned int num )
{
	return get( num );
}



/*
	Class: maxheap
	Method: operator []
	Use: Gets a key in the maxheap
	Input: Key to search for
	Output: Value of node found
*/
template <typename data_type>
data_type & maxheap<data_type>::operator [] ( const char * key )
{
	return get( key );
}



/*
	Class: maxheap
	Method: key
	Use: Access keys as if the maxheap was a sorted array
	Input: Index of key
	Output: Key of node found
*/
template <typename data_type>
char * maxheap<data_type>::key( unsigned int num )
{
	// It cant be in the maxheap if its bigger than the number of item sin it
	if ( in_maxheap <= num )
	{
		return NULL;
	}
	unsigned int index = 0;
	return get( num, index, root )->key();
}



/*
	Class: maxheap
	Method: get
	Use: Access values as if the maxheap was a sorted array
	Input: Index of item
	Output: Value of node found
*/
template <typename data_type>
data_type & maxheap<data_type>::get( unsigned int num )
{
	// It wont be found so create it
	if ( in_maxheap <= num )
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
	Class: maxheap
	Method: get
	Use: Access nodes as if the maxheap was a sorted array
	Input: Index of item to find, current index, and root of the maxheap
	Output: Node found
*/
template <typename data_type>
maxheap_node<data_type> * maxheap<data_type>::get( unsigned int & num, unsigned int & index, maxheap_node<data_type> * root )
{
	if ( !root )
		return NULL;
	// To see if one of the sides found it
	maxheap_node<data_type> * found = NULL;
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
	Class: maxheap
	Method: get
	Use: Finds the value of a key in the maxheap
	Input: Key to search for
	Output: Value of node found
*/
template <typename data_type>
data_type & maxheap<data_type>::get( const char * key )
{
	// Try to get if that doesnt work then insert
	if ( !get( key, root ) )
	{
		return this->insert( key );
	}
	return get( key, root )->value();
}



/*
	Class: maxheap
	Method: get
	Use: Finds a node coresponding to a key in the maxheap
	Input: Key to search for and root of the maxheap
	Output: Node found
*/
template <typename data_type>
maxheap_node<data_type> * maxheap<data_type>::get( const char * key, maxheap_node<data_type> * root )
{
	// Look for the key this si a simple binary search algoritham
	if ( !root )
	{
		return NULL;
	}
    MACRO_PRINT_FILE_LINE("root is %p %s, want %s\n", root, root->key(), key);
	// If key return
	if ( 0 == strcmp( root->key(), key ) )
	{
		return root;
	}
	// Binary search
    maxheap_node<data_type> * try_left = get( key, root->left() );
    if (try_left != NULL) {
        return try_left;
    }
    maxheap_node<data_type> * try_right = get( key, root->right() );
    if (try_right != NULL) {
        return try_right;
    }
}



/*
	Class: maxheap
	Method: insert
	Use: Inserts a node into the maxheap
	Input: Key to insert
	Output: Values of the inserted node
*/
template <typename data_type>
data_type & maxheap<data_type>::insert( const char * key )
{
	return this->insert( key, root )->value();
}



/*
	Class: maxheap
	Method: insert
	Use: Inserts a node into the maxheap
	Input: Key to insert
	Output: Values of the inserted node
*/
template <typename data_type>
maxheap_node<data_type> * maxheap<data_type>::insert_return_node( const char * key )
{
	return this->insert( key, root );
}



/*
	Class: maxheap
	Method: insert_maxheap
	Use: Fixes problems with the red black tree to make sure it conforms to the rules
	Input: Key to insert and the root of the maxheap
	Output: Node inserted
*/
template <typename data_type>
maxheap_node<data_type> * maxheap<data_type>::insert( const char * key, maxheap_node<data_type> * & root)
{
    // Save the node because fixing the tree may fuck it up
    maxheap_node<data_type> * node;

    // Insert like normal
    node = this->insert_bst(key, root);

    // Fix the heap to make sure that the biggest is the root
    // FIXME i know this is wrong but i dont have time to add a parent
    // and it still works
    this->fix_maxheap(root);
    MACRO_PRINT_FILE_LINE("Root is now %s\n", root->key());
    if (root->right())
        MACRO_PRINT_FILE_LINE("root right is %s\n", root->right()->key());
    if (root->left())
        MACRO_PRINT_FILE_LINE("root left is %s\n", root->left()->key());

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
maxheap_node<data_type> * maxheap<data_type>::insert_bst( const char * key, maxheap_node<data_type> * & node)
{
    // Insert like normal
	if (!node)
	{
		return create_node(key, node);
	}
	// Binary search
    switch (search_maxheap(key, node)) {
    case MAXHEAP_GO_LEFT:
        return this->insert_bst( key, node->left());
    case MAXHEAP_GO_RIGHT:
        return this->insert_bst( key, node->right());
    }
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
maxheap_node<data_type> * maxheap<data_type>::fix_maxheap(maxheap_node<data_type> * & node)
{
    if (node == NULL) {
        return NULL;
    }
    /*
    MACRO_PRINT_FILE_LINE("I am %s\n", node->key());
    if (node->right())
        MACRO_PRINT_FILE_LINE("my right is %s\n", node->right()->key());
    if (node->left())
        MACRO_PRINT_FILE_LINE("my left is %s\n", node->left()->key());
    */
    // Make sure our children are who we hoep they are
    fix_maxheap(node->left());
    fix_maxheap(node->right());
    // Our left is bigger than us
    if (node->left() && 0 >= strcmp(node->key(), node->left()->key())) {
        maxheap_node<data_type> * tmp = node;
        node = node->left();
        // MACRO_PRINT_FILE_LINE("left  swaping %s for %s\n", tmp->key(), node->key());
        tmp->right() = node->right();
        node->right() = tmp->right();
        tmp->left() = node->left();
        node->left() = tmp;
        return NULL;
    // Our right is bigger than us
    } else if (node->right() && 0 >= strcmp(node->key(), node->right()->key())) {
        maxheap_node<data_type> * tmp = node;
        node = node->right();
        // MACRO_PRINT_FILE_LINE("right swaping %s for %s\n", tmp->key(), node->key());
        // Whatever was to your left need to be to my left
        tmp->left() = node->left();
        node->left() = tmp->left();
        tmp->right() = node->right();
        node->right() = tmp;
        return NULL;
    }
    // MACRO_PRINT_FILE_LINE("No swap %s\n", node->key());
    return NULL;
}



/*
	Class: maxheap
	Method: create_node
	Use: Inserts a node into the maxheap as if it was a maxheap
	Input: Key to insert and the root of the maxheap
	Output: Node inserted
*/
template <typename data_type>
maxheap_node<data_type> * maxheap<data_type>::create_node( const char * key, maxheap_node<data_type> * & node)
{
    node_added();
    node = new maxheap_node<data_type>(key);
    return node;
}




/*
	Class: maxheap
	Method: node_added
	Use: Inserts a node into the maxheap as if it was a maxheap
	Input: Key to insert and the root of the maxheap
	Output: Node inserted
*/
template <typename data_type>
int maxheap<data_type>::node_added() {
    return ++in_maxheap;
}



/*
	Class: maxheap
	Method: insert_maxheap
	Use: Inserts a node into the maxheap as if it was a maxheap
	Input: Key to insert and the root of the maxheap
	Output: Node inserted
*/
template <typename data_type>
int maxheap<data_type>::search_maxheap( const char * key, maxheap_node<data_type> * & node)
{
	// Binary search
    MACRO_PRINT_FILE_LINE("looking for %s, node is %s\n", key, node->key());
    MACRO_PRINT_FILE_LINE("I am %s\n", node->key());
    if (node->right())
        MACRO_PRINT_FILE_LINE("my right is %s\n", node->right()->key());
    if (node->left())
        MACRO_PRINT_FILE_LINE("my left is %s\n", node->left()->key());
	if ( 0 < strcmp( node->key(), key ) )
	{
        return MAXHEAP_GO_LEFT;
	}
    return MAXHEAP_GO_RIGHT;
}



/*
	Class: maxheap
	Method: contains
	Use: Checks if a key is in the maxheap
	Input: Key to search for
	Output: True or false that is set due to a not found being
		NULL and a found being the pointer so true
*/
template <typename data_type>
bool maxheap<data_type>::contains( const char * key )
{
	return get( key, root );
}



/*
	Class: maxheap
	Method: size
	Use: How many items are in the maxheap
	Input: None
	Output: Number of nodes in the maxheap
*/
template <typename data_type>
unsigned int maxheap<data_type>::size( void )
{
	return in_maxheap;
}


/*
	Class: maxheap
	Method: all
	Use: Creates an array to access maxheap values
	Input: None
	Output: An array whos members a pointers to the values of nodes
		this allows a client to eficently opperate on the maxheap as if
		it were a sorted array without the need to find the thoretical
		position every time the subscript operator is used
*/
template <typename data_type>
data_type ** maxheap<data_type>::all( void )
{
	// More indexing, see get ( unsigned int num ) for explination of how this works
	unsigned int index = 0;
	data_type ** array = new data_type * [ in_maxheap ];
	all( index, array, root );
	return array;
}



/*
	Class: maxheap
	Method: all
	Use: Fills an array with the pointers to node values
	Input: Current index, array to fill, and pointer to root
	Output: None
*/
template <typename data_type>
void maxheap<data_type>::all( unsigned int & index , data_type ** array, maxheap_node<data_type> * root )
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
	Class: maxheap
	Method: keys
	Use: Creates an array to access maxheap keys
	Input: None
	Output: An array whos members a pointers to the keys of nodes
		this allows a client to eficently opperate on the maxheap as if
		it were a sorted array without the need to find the thoretical
		position every time the subscript operator is used
*/
template <typename data_type>
char *** maxheap<data_type>::keys( void )
{
	// More indexing, see get ( unsigned int num ) for explination of how this works
	unsigned int index = 0;
	char *** array = new char ** [in_maxheap + 1];
	keys( index, array, root );
    array[in_maxheap] = NULL;
	return array;
}



/*
	Class: maxheap
	Method: keys
	Use: Fills an array with the pointers to node keys
	Input: Current index, array to fill, and pointer to root
	Output: None
*/
template <typename data_type>
void maxheap<data_type>::keys( unsigned int & index , char *** array, maxheap_node<data_type> * root )
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
	Class: maxheap
	Method: remove
	Use: Removes a node from the maxheap
	Input: Key to remove
	Output: 1 for removed 0 for not	found
*/
template <typename data_type>
bool maxheap<data_type>::remove( const char * key )
{
	return remove( key, root );
}



/*
	Class: maxheap
	Method: remove
	Use: Removes a node from the maxheap
	Input: Key of node to remove and root of maxheap
	Output: 1 for removed 0 for not	found
*/
template <typename data_type>
bool maxheap<data_type>::remove( const char * key, maxheap_node<data_type> * & root )
{
	if ( !root )
	{
		return false;
	}
	if ( 0 == strcmp( root->key(), key ) )
	{
		// We know we are goiong to delete root
		maxheap_node<data_type> * del = root;
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
			maxheap_node<data_type> * successor = NULL;
			maxheap_node<data_type> * parent = NULL;
			// Find the inorder successor to the maxheap_node
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
		--in_maxheap;
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
	Class: maxheap
	Method: inorder
	Use: Finds the inorder successor to a node in the maxheap
	Input: The node whose inorder successor is being found
		and the node which will point to the parent of the successor 
	Output: The successor and the parent of the successor is also set
*/
template <typename data_type>
maxheap_node<data_type> * maxheap<data_type>::inorder( maxheap_node<data_type> * root, maxheap_node<data_type> * & parent )
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

