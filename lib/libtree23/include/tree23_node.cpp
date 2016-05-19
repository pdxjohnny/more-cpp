#include "libtree23.h"
#include <libmacro.h>

#ifndef LIBTREE23_TREE23_NODE
#define LIBTREE23_TREE23_NODE

// Constructor
template <typename data_type>
tree23_node<data_type>::tree23_node() : data(NULL), active(NULL) {
    data = new data_type [2];
    active = new bool [2];
    active[TREE23_LEFT] = false;
    active[TREE23_RIGHT] = false;
}

// Destructor
template <typename data_type>
tree23_node<data_type>::~tree23_node() {
    if (active != NULL) {
        delete[] active;
    }
    if (data != NULL) {
        delete[] data;
    }
}

// Copies the data of the node
template <typename data_type>
tree23_node_basic & tree23_node<data_type>::operator=(const tree23_node_basic & copy) {
    tree23_node_basic::operator=(copy);
    const tree23_node<data_type> * copy_ptr = dynamic_cast<const tree23_node<data_type> *>(&copy);
    if (this == copy_ptr) {
        return *this;
    }
    // Nothing to copy or bad typecast
    if (copy_ptr == NULL) {
        return *this;
    }
    if (data != NULL && copy_ptr->data != NULL) {
        data[TREE23_LEFT] = copy_ptr->data[TREE23_LEFT];
        data[TREE23_RIGHT] = copy_ptr->data[TREE23_RIGHT];
    }
    if (active != NULL && copy_ptr->active != NULL) {
        active[TREE23_LEFT] = copy_ptr->active[TREE23_LEFT];
        active[TREE23_RIGHT] = copy_ptr->active[TREE23_RIGHT];
    }
    return *this;
}

// Adds a node to the end of the tree23_basic
template <typename data_type>
data_type * tree23_node<data_type>::add(data_type & to_add) {
    // Neither are active, set the left
    if (!active[TREE23_LEFT] && !active[TREE23_RIGHT]) {
        data[TREE23_LEFT] = to_add;
        active[TREE23_LEFT] = true;
    }
    // Leaf node cases
    if (node(TREE23_LEFT) == NULL && node(TREE23_MIDDLE) == NULL &&
            node(TREE23_RIGHT) == NULL) {
        if (active[TREE23_LEFT] && !active[TREE23_RIGHT]) {
            active[TREE23_RIGHT] = true;
            if (to_add < data[TREE23_LEFT]) {
                // Left is active and less than left
                data[TREE23_RIGHT] = data[TREE23_LEFT];
                data[TREE23_LEFT] = to_add;
            } else {
                // Left is active and greaterthan or equal to left
                data[TREE23_RIGHT] = to_add;
            }
        } else if (active[TREE23_RIGHT] && active[TREE23_LEFT]) {
            // Both active choose who to send up
            if (to_add < data[TREE23_LEFT]) {
                // Less than left, left is middle send up left
                data_type send_up = new data_type(data[TREE23_LEFT]);
                data[TREE23_LEFT] = to_add;
                return send_up;
            } else if (to_add >= data[TREE23_RIGHT]) {
                // Greater than or equal to the right, right is middle send up right
                data_type send_up = new data_type(data[TREE23_RIGHT]);
                data[TREE23_RIGHT] = to_add;
                return send_up;
            } else {
                // Data to add is in between left and right it is the middle so
                // send it up
                data_type send_up = new data_type(to_add);
                return send_up;
            }
        }
    } else {
        if (active[TREE23_LEFT] && !active[TREE23_RIGHT]) {
            // Left is active right is not
            if (to_add < data[TREE23_LEFT]) {
                // Left is active and less than left
                push_up(node(TREE23_LEFT)->add(to_add), TREE23_LEFT);
            } else {
                // Left is active and greater than or equal to left
                push_up(node(TREE23_RIGHT)->add(to_add), TREE23_RIGHT);
            }
        } else if (active[TREE23_RIGHT] && active[TREE23_LEFT]) {
            // Both active so we have a middle because we are not a leaf
            if (to_add < data[TREE23_LEFT]) {
                // Both active and less than left
                push_up(node(TREE23_LEFT)->add(to_add), TREE23_LEFT);
            } else if (to_add >= data[TREE23_RIGHT]) {
                // Both active and greater than or equal to right
                push_up(node(TREE23_RIGHT)->add(to_add), TREE23_RIGHT);
            } else {
                // Both active and in between left and right
                push_up(node(TREE23_MIDDLE)->add(to_add), TREE23_MIDDLE);
            }
        }
    }
    return NULL;
}

// If add returns a node then it is pushing that node up. This handles the
// pushing up of a node
template <typename data_type>
bool tree23_node<data_type>::add_root(tree23_node<data_type> * root, data_type & add_data) {
    return push_up(add(add_data), TREE23_MIDDLE);
}

// Sets the left to the data and marks the right as inactive
template <typename data_type>
tree23_node<data_type> & tree23_node<data_type>::set(data_type & set_to) {
    data[TREE23_LEFT] = set_to;
    active[TREE23_LEFT] = true;
    active[TREE23_RIGHT] = false;
    return *this;
}

// Returns a left which holds the left data of this node and this node should
// be treated as the right
template <typename data_type>
tree23_node<data_type> * tree23_node<data_type>::split() {
    // Create the new node adn give it our left data
    tree23_node<data_type> ** both = new tree23_node<data_type> * [2];
    both[TREE23_LEFT] = new tree23_node<data_type>;
    both[TREE23_RIGHT] = new tree23_node<data_type>;
    both[TREE23_LEFT]->add(data[TREE23_LEFT]);
    both[TREE23_RIGHT]->add(data[TREE23_RIGHT]);
    // We now hold nothing
    active[TREE23_LEFT] = false;
    active[TREE23_RIGHT] = false;
    return both;
}

// Splits off the right into a new node and the left remains stored in the node
// called on
template <typename data_type>
tree23_node<data_type> * tree23_node<data_type>::rsplit() {
    // Create the new node adn give it our right data
    tree23_node<data_type> * new_right = new tree23_node<data_type>;
    new_right->add(data[TREE23_RIGHT]);
    active[TREE23_RIGHT] = false;
    return new_right;
}

// If add returns a node then it is pushing that node up. This handles the
// pushing up of a node
template <typename data_type>
bool tree23_node<data_type>::push_up(data_type * pushed_up, int loc) {
    // Nothing pushed up
    if (pushed_up == NULL) {
        return false;
    }
    // If the child was full and I am full
    if (active[TREE23_RIGHT] && active[TREE23_LEFT]) {
        tree23_node<data_type> ** both = split();
        // If the middle was full
        if (TREE23_MIDDLE == loc) {
            add(pushed_up);
            if (node(TREE23_MIDDLE) != NULL) {
                both[TREE23_RIGHT]->node(TREE23_LEFT) = node(TREE23_MIDDLE)->rsplit();
                both[TREE23_RIGHT]->node(TREE23_RIGHT) = node(TREE23_RIGHT);
                both[TREE23_LEFT]->node(TREE23_RIGHT) = node(TREE23_MIDDLE);
                both[TREE23_LEFT]->node(TREE23_LEFT) = node(TREE23_LEFT);
            }
        // If the right was full
        } else if (TREE23_RIGHT == loc) {
            // Our right is our data
            set(data[TREE23_RIGHT]);
            // Our new right holds the node that was pushed up
            both[TREE23_RIGHT]->set(pushed_up);
            if (node(TREE23_RIGHT) != NULL) {
                both[TREE23_RIGHT]->node(TREE23_RIGHT) = node(TREE23_RIGHT)->rsplit();
                both[TREE23_RIGHT]->node(TREE23_LEFT) = node(TREE23_RIGHT);
                both[TREE23_LEFT]->node(TREE23_RIGHT) = node(TREE23_MIDDLE);;
                both[TREE23_LEFT]->node(TREE23_LEFT) = node(TREE23_LEFT);
            }
        // If the left was full
        } else {
            // Our left is our data
            set(data[TREE23_LEFT]);
            // Our new left holds the node that was pushed up
            both[TREE23_LEFT]->set(pushed_up);
            if (node(TREE23_LEFT) != NULL) {
                both[TREE23_RIGHT]->node(TREE23_LEFT) = node(TREE23_MIDDLE);
                both[TREE23_RIGHT]->node(TREE23_RIGHT) = node(TREE23_RIGHT);
                both[TREE23_LEFT]->node(TREE23_RIGHT) = node(TREE23_LEFT)->rsplit();
                both[TREE23_LEFT]->node(TREE23_LEFT) = node(TREE23_LEFT);
            }
        }
        // Set our left and right to the correct values
        node(TREE23_LEFT) = both[TREE23_LEFT];
        node(TREE23_RIGHT) = both[TREE23_RIGHT];
        // We no longer have a middle
        node(TREE23_MIDDLE) = NULL;
        delete[] both;
    // Child is full and I have one in use
    } else if (TREE23_RIGHT == loc) {
        active[TREE23_RIGHT] = true;
        data[TREE23_RIGHT] = pushed_up;
        tree23_node<data_type> * tmp = nodes(TREE23_RIGHT);
        nodes(TREE23_RIGHT) = tmp->rsplit();
        nodes(TREE23_MIDDLE) = tmp;
    // Left
    } else {
        active[TREE23_RIGHT] = true;
        data[TREE23_RIGHT] = data[TREE23_LEFT];
        data[TREE23_LEFT] = pushed_up;
        nodes(TREE23_MIDDLE) = nodes(TREE23_LEFT)->rsplit();
    }
    return false;
}

// Creates a node of the correct type
template <typename data_type>
bool tree23_node<data_type>::create(tree23_node_basic *& node) {
    tree23_node * tmp = new tree23_node<data_type>;
    tmp->active[TREE23_LEFT] = true;
    node = tmp;
    return (node != NULL);
}

/*
 * If remove self is called the caller needs to be aware that this does not
 * update the left pointer of the node previous to this one and will break the
 * list. If this is the root pointer then that doesnt matter because there is
 * no previous poitner. However if you have the pointer previous to this it is
 * preferable to all the remove(index) function so that the left poitners of
 * the tree23 will be updated correctly
 */
template <typename data_type>
tree23_node_basic * tree23_node<data_type>::remove_self(tree23_node_basic *& replace) {
    delete this;
    return replace;
}

// Return the value we are managing
template <typename data_type>
data_type & tree23_node<data_type>::value(int index) {
    return data[index];
}

/*
 * Attempts to get a node at the given index and counts along the way
 */
template <typename data_type>
tree23_node_basic * tree23_node<data_type>::get_count(int & index, int & curr) {
	// To see if one of the sides found it
    tree23_node_basic * found = NULL;
	// Look of the index on the left, that will be index 0 if its the leftmost node
    if (node(TREE23_LEFT) != NULL) {
        found = node(TREE23_LEFT)->get_count(index, curr);
        if (found) {
            return found;
        }
    }
	// Check if this node is the index
	if (index == curr) {
		return this;
	}
	// increment the index
	++curr;
	// Look of the index on the right
    if (node(TREE23_RIGHT) != NULL) {
        found = node(TREE23_RIGHT)->get_count(index, curr);
        if (found) {
            return found;
        }
    }
	return NULL;
}

/*
 * Attempts to remove a node at the given index and counts along the way
 */
template <typename data_type>
bool tree23_node<data_type>::remove_count(int & index, int & curr) {
    /*
    // We want to remove the left one but we cant because there is
    // nothing to remove
    if (left == NULL) {
        return false;
    }
    // If we are on the index we wish to remove then try to remove it
    if (index == curr) {
        // Store the node
        tree23_node_basic * tmp = left;
        // Set our left to be thenode we are removings left
        left = left->left;
        // Remove the target
        delete tmp;
        // Return true for yes we removed
        return true;
    }
    return left->remove_count(index, ++curr);
    */
    return true;
}
#endif
