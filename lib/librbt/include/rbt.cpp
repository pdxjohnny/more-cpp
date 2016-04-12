/*
	Author: John Andersen
	Date: 02/19/2015
	Description: Binary Tree
*/
#include "librbt.h"

#ifndef RBT_METHODS
#define RBT_METHODS

/*
	Class: rbt
	Method: Constructor
	Use: Initialises data members
	Input: None
	Output: None
*/
template <typename data_type>
rbt<data_type>::rbt()
{
	init();
}



/*
	Class: rbt
	Method: Destructor
	Use: Deallocates all nodes
	Input: None
	Output: None
*/
template <typename data_type>
rbt<data_type>::~rbt()
{
	destroy();
}



/*
	Class: rbt
	Method: init
	Use: Initialises data members
	Input: None
	Output: None
*/
template <typename data_type>
void rbt<data_type>::init( void )
{
	root = NULL;
	in_rbt = 0;
}



/*
	Class: rbt
	Method: destroy
	Use: Deallocates all nodes
	Input: None
	Output: None
*/
template <typename data_type>
void rbt<data_type>::destroy( void )
{
	destroy( root );
	in_rbt = 0;
}



/*
	Class: rbt
	Method: destroy
	Use: Deallocates all nodes recursivly
	Input: Root of rbt
	Output: None
*/
template <typename data_type>
void rbt<data_type>::destroy( rbt_node<data_type> * & root )
{
	if ( !root )
		return;
	// Go down booth sides
	destroy( root->left );
	destroy( root->right );
	// Deallocate the key string
	delete [] root->key;
	// Delete the node
	delete root;
	// Set to to NULL
	root = NULL;
}



/*
	Class: rbt
	Method: operator []
	Use: Access values as if the rbt was a sorted array
	Input: Index of item
	Output: Value of node found
*/
template <typename data_type>
data_type & rbt<data_type>::operator [] ( unsigned int num )
{
	return get( num );
}



/*
	Class: rbt
	Method: operator []
	Use: Gets a key in the rbt
	Input: Key to search for
	Output: Value of node found
*/
template <typename data_type>
data_type & rbt<data_type>::operator [] ( char * key )
{
	return get( key );
}



/*
	Class: rbt
	Method: key
	Use: Access keys as if the rbt was a sorted array
	Input: Index of key
	Output: Key of node found
*/
template <typename data_type>
char * rbt<data_type>::key( unsigned int num )
{
	// It cant be in the rbt if its bigger than the number of item sin it
	if ( in_rbt <= num )
	{
		return NULL;
	}
	unsigned int index = 0;
	return get( num, index, root )->key;
}



/*
	Class: rbt
	Method: get
	Use: Access values as if the rbt was a sorted array
	Input: Index of item
	Output: Value of node found
*/
template <typename data_type>
data_type & rbt<data_type>::get( unsigned int num )
{
	// It wont be found so create it
	if ( in_rbt <= num )
	{
		char key [20];
		sprintf( key, "%d", num );
		return insert( key );
	}
	// Find it
	unsigned int index = 0;
	return get( num, index, root )->value;
}



/*
	Class: rbt
	Method: get
	Use: Access nodes as if the rbt was a sorted array
	Input: Index of item to find, current index, and root of the rbt
	Output: Node found
*/
template <typename data_type>
rbt_node<data_type> * rbt<data_type>::get( unsigned int & num, unsigned int & index, rbt_node<data_type> * root )
{
	if ( !root )
		return NULL;
	// To see if one of the sides found it
	rbt_node<data_type> * found = NULL;
	// Look of the index on the left, that will be index 0 if its the leftmost node
	found = get( num, index, root->left );
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
	found = get( num, index, root->right );
	if ( found )
	{
		return found;
	}
	return NULL;
}



/*
	Class: rbt
	Method: get
	Use: Finds the value of a key in the rbt
	Input: Key to search for
	Output: Value of node found
*/
template <typename data_type>
data_type & rbt<data_type>::get( char * key )
{
	// Try to get if that doesnt work then insert
	if ( !get( key, root ) )
	{
		return insert( key );
	}
	return get( key, root )->value;
}



/*
	Class: rbt
	Method: get
	Use: Finds a node coresponding to a key in the rbt
	Input: Key to search for and root of the rbt
	Output: Node found
*/
template <typename data_type>
rbt_node<data_type> * rbt<data_type>::get( char * key, rbt_node<data_type> * root )
{
	// Look for the key this si a simple binary search algoritham
	if ( !root )
	{
		return NULL;
	}
	// If key return
	if ( 0 == strcmp( root->key, key ) )
	{
		return root;
	}
	// If less go left
	else if ( 0 < strcmp( root->key, key ) )
	{
		return get( key, root->left );
	}
	// If greater than or equal to go right
	return get( key, root->right );
}



/*
	Class: rbt
	Method: insert
	Use: Inserts a node into the rbt
	Input: Key to insert
	Output: Values of the inserted node
*/
template <typename data_type>
data_type & rbt<data_type>::insert( char * key )
{
	return insert( key, root )->value;
}



/*
	Class: rbt
	Method: insert
	Use: Inserts a node into the rbt
	Input: Key to insert
	Output: Values of the inserted node
*/
template <typename data_type>
rbt_node<data_type> * rbt<data_type>::insert_return_node( char * key )
{
	return insert( key, root );
}



/*
	Class: rbt
	Method: insert_rbt
	Use: Fixes problems with the red black tree to make sure it conforms to the rules
	Input: Key to insert and the root of the rbt
	Output: Node inserted
*/
template <typename data_type>
rbt_node<data_type> * rbt<data_type>::insert( char * key, rbt_node<data_type> * & root)
{
    // Save the node because fixing the tree may fuck it up
    rbt_node<data_type> * node;
    rbt_node<data_type> * parent = NULL;

    // Insert like normal
    node = insert_bst(key, root, parent);

    // Now it has been inserted and is red begin the case correction
    insert_rbt(node);

    return node;
}



/*
	Class: rbt
	Method: insert
	Use: Inserts a node into the rbt as bst then fixes it to make it a rbt
	Input: Key to insert and the root of the rbt
	Output: Node inserted
*/
template <typename data_type>
rbt_node<data_type> * rbt<data_type>::insert_rbt(rbt_node<data_type> * & node)
{
    // After normal insertion the node is red
    // If there is no parent then we are the root
    if (node->up == NULL) {
        // Root must always be black
        node->color = RBT_BLACK;
    // After insertion the node is red, we cant have two reds in a row because
    // a red node can never have a red child but a black node can have a black
    // child
    } else if (node->up->color == RBT_RED) {
        // pp, the parents parent
        rbt_node<data_type> * pp = node->up->up;
        // We now need to change the color of the parent the parents parent and
        // the uncle of this node. So were red our parent is red so the
        // grandparent must be black. All the colors need to switch so parent
        // becomes black grandparent becomes black and if we have an uncle the
        // uncle needs to switch colors too because its parent switched
        if (pp != NULL) {
            // The grandparent has a left and the left is our uncle because it
            // is not our parent
            if (pp->left != node->up) {
                // Treat NULL as being black, uncle is black
                if (pp->left == NULL || pp->left->color == RBT_BLACK) {
                    // Parent is red and grandparent and left uncle are black
                    // we need to rotate the tree and then change the color of
                    // the parent grandparent and uncle, we will rotate left
                    // becasue the uncle is on the left so we know we are on
                    // the right
                    rotate_left(node->up);
                    // Now switch the colors
                    node->up->color = RBT_BLACK;
                    pp->color = RBT_RED;
                // Uncle is red
                } else {
                    // Change the colors
                    if (pp->left != NULL) {
                        pp->left->color = RBT_BLACK;
                    }
                    node->up->color = RBT_BLACK;
                    pp->color = RBT_RED;
                    // Correct anything we messed up with the granparent
                    insert_rbt(pp);
                }
            // The grandparent has a right and the right is our uncle because it
            // is not our parent
            } else if (pp->right != node->up) {
                // Treat NULL as being black, uncle is black
                if (pp->right == NULL || pp->right->color == RBT_BLACK) {
                    // Parent is red and grandparent and right uncle are black
                    // we need to rotate the tree and then change the color of
                    // the parent grandparent and uncle, we will rotate right
                    // becasue the uncle is on the right so we know we are on
                    // the left
                    rotate_right(node->up);
                    // Now switch the colors
                    node->up->color = RBT_BLACK;
                    pp->color = RBT_RED;
                // Uncle is red
                } else {
                    // Change the colors
                    if (pp->right != NULL) {
                        pp->right->color = RBT_BLACK;
                    }
                    node->up->color = RBT_BLACK;
                    pp->color = RBT_RED;
                    // Correct anything we messed up with the granparent
                    insert_rbt(pp);
                }
            }
        }
    }
    return node;
}

template <typename data_type>
void rbt<data_type>::rotate_left(rbt_node<data_type> * node) {
    // If we are to the right of our parent
    if (node->up != NULL && node->up->right == node) {
        // Your left becomes your parents right
        node->up->right = node->left;
        // Parent becomes left of node
        node->left = node->up;
        // Parents parent becomes your parent
        node->up = node->up->up;
        // Parent of old parent is node
        node->left->up = node;
    }
}

template <typename data_type>
void rbt<data_type>::rotate_right(rbt_node<data_type> * node) {
    // If we are to the left of our parent
    if (node->up != NULL && node->up->left == node) {
        // Your right becomes your parents left
        node->up->left = node->right;
        // Parent becomes right of node
        node->right = node->up;
        // Parents parent becomes your parent
        node->up = node->up->up;
        // Parent of old parent is node
        node->right->up = node;
    }
}

/*
	Class: rbt
	Method: insert_bst
	Use: Inserts a node into the rbt as if it was a bst
	Input: Key to insert and the root of the rbt
	Output: Node inserted
*/
template <typename data_type>
rbt_node<data_type> * rbt<data_type>::insert_bst( char * key, rbt_node<data_type> * & node, rbt_node<data_type> * & prev)
{
    // Insert like normal
	if (!node)
	{
		node = new rbt_node<data_type>;
		// allocate the key
		node->key = new char [ strlen( key ) + 1 ];
		strcpy( node->key, key );
		// Make sure left and right are null
		node->left = node->right = NULL;
        // Up is whatever the previous node was
        node->up = prev;
        // Make it red
        node->color = RBT_RED;
		++in_rbt;
		return node;
	}
	// Binary search
	else if ( 0 < strcmp( node->key, key ) )
	{
		return insert_bst( key, node->left, node );
	}
	return insert_bst( key, node->right, node );
}



/*
	Class: rbt
	Method: contains
	Use: Checks if a key is in the rbt
	Input: Key to search for
	Output: True or false that is set due to a not found being
		NULL and a found being the pointer so true
*/
template <typename data_type>
bool rbt<data_type>::contains( char * key )
{
	return get( key, root );
}



/*
	Class: rbt
	Method: size
	Use: How many items are in the rbt
	Input: None
	Output: Number of nodes in the rbt
*/
template <typename data_type>
unsigned int rbt<data_type>::size( void )
{
	return in_rbt;
}


/*
	Class: rbt
	Method: all
	Use: Creates an array to access rbt values
	Input: None
	Output: An array whos members a pointers to the values of nodes
		this allows a client to eficently opperate on the rbt as if
		it were a sorted array without the need to find the thoretical
		position every time the subscript operator is used
*/
template <typename data_type>
data_type ** rbt<data_type>::all( void )
{
	// More indexing, see get ( unsigned int num ) for explination of how this works
	unsigned int index = 0;
	data_type ** array = new data_type * [ in_rbt ];
	all( index, array, root );
	return array;
}



/*
	Class: rbt
	Method: all
	Use: Fills an array with the pointers to node values
	Input: Current index, array to fill, and pointer to root
	Output: None
*/
template <typename data_type>
void rbt<data_type>::all( unsigned int & index , data_type ** array, rbt_node<data_type> * root )
{
	// More indexing, see get ( unsigned int num ) for explination of how this works
	if ( !root )
		return;
	all( index, array, root->left );
	array[ index ] = & root->value;
	++index;
	all( index, array, root->right );
	return;
}



/*
	Class: rbt
	Method: keys
	Use: Creates an array to access rbt keys
	Input: None
	Output: An array whos members a pointers to the keys of nodes
		this allows a client to eficently opperate on the rbt as if
		it were a sorted array without the need to find the thoretical
		position every time the subscript operator is used
*/
template <typename data_type>
char ** rbt<data_type>::keys( void )
{
	// More indexing, see get ( unsigned int num ) for explination of how this works
	unsigned int index = 0;
	char ** array = new char * [ in_rbt ];
	keys( index, array, root );
	return array;
}



/*
	Class: rbt
	Method: keys
	Use: Fills an array with the pointers to node keys
	Input: Current index, array to fill, and pointer to root
	Output: None
*/
template <typename data_type>
void rbt<data_type>::keys( unsigned int & index , char ** array, rbt_node<data_type> * root )
{
	// More indexing, see get ( unsigned int num ) for explination of how this works
	if ( !root )
		return;
	keys( index, array, root->left );
	array[ index ] = root->key;
	++index;
	keys( index, array, root->right );
	return;
}



/*
	Class: rbt
	Method: remove
	Use: Removes a node from the rbt
	Input: Key to remove
	Output: 1 for removed 0 for not	found
*/
template <typename data_type>
bool rbt<data_type>::remove( char * key )
{
	return remove( key, root );
}



/*
	Class: rbt
	Method: remove
	Use: Removes a node from the rbt
	Input: Key of node to remove and root of rbt
	Output: 1 for removed 0 for not	found
*/
template <typename data_type>
bool rbt<data_type>::remove( char * key, rbt_node<data_type> * & root )
{
	if ( !root )
	{
		return false;
	}
	if ( 0 == strcmp( root->key, key ) )
	{
		// We know we are goiong to delete root
		rbt_node<data_type> * del = root;
		// If its a leaf then no problem delete
		if ( !root->left && !root->right )
		{
			root = NULL;
		}
		// If it has a left and not a right just replace
		else if ( root->left && !root->right )
		{
			root = root->left;
		}
		// If it has a right and not a left just replace
		else if ( root->right && !root->left )
		{
			root = root->right;
		}
		// If it has two children
		else
		{
			// Find inorder successor
			rbt_node<data_type> * successor = NULL;
			rbt_node<data_type> * parent = NULL;
			// Find the inorder successor to the rbt_node
			successor = inorder( root, parent );
			// Set the left of the parent of the inorder
			// to the inorder's right, it will have no left
			// if it did then it wouldn't be the inorder
			successor->left = root->left;
			if ( parent )
				parent->left = successor->right;
			// Make suer we arent seting the right to ourself
			if ( parent && parent->right != root->right )
				successor->right = root->right;
			root = successor;
		}
		// Delete
		delete [] del->key;
		delete del;
		--in_rbt;
		return true;
	}
	// Binary search
	else if ( 0 < strcmp( root->key, key ) )
	{
		return remove( key, root->left );
	}
	return remove( key, root->right );
}



/*
	Class: rbt
	Method: inorder
	Use: Finds the inorder successor to a node in the rbt
	Input: The node whose inorder successor is being found
		and the node which will point to the parent of the successor 
	Output: The successor and the parent of the successor is also set
*/
template <typename data_type>
rbt_node<data_type> * rbt<data_type>::inorder( rbt_node<data_type> * root, rbt_node<data_type> * & parent )
{
	// Goes right then all the way left and returns
	if ( !root )
	{
		return NULL;
	}
	if ( root->right )
	{
		parent = root;
		root = root->right;
	}
	while ( root->left )
	{
		parent = root;
		root = root->left;
	}
	return root;
}

#endif

