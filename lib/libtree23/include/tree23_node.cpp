#include "libtree23.h"
#include <libmacro.h>

#ifndef LIBTREE23_TREE23_NODE
#define LIBTREE23_TREE23_NODE

// Constructor
template <typename data_type>
tree23_node<data_type>::tree23_node() : {
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
    const tree23_node<data_type> * copy_ptr = dynamic_cast<const tree23_node<data_type> *>(&copy);
    if (this == copy_ptr) {
        return *this;
    }
    if (data != NULL && copy_ptr->data != NULL) {
        this->data[TREE23_LEFT] = copy_ptr->data[TREE23_LEFT];
        this->data[TREE23_RIGHT] = copy_ptr->data[TREE23_RIGHT];
    }
    if (active != NULL && copy_ptr->active != NULL) {
        active[TREE23_LEFT] = copy_ptr->active[TREE23_LEFT];
        active[TREE23_RIGHT] = copy_ptr->active[TREE23_RIGHT];
    }
    return *this;
}

// Adds a node to the end of the tree23_basic
template <typename data_type>
data_type * tree23_node<data_type>::add(data_type & add_data) {
    // Leaf node cases
    if (this->node(TREE23_LEFT) == NULL && this->node(TREE23_MIDDLE) == NULL &&
            this->node(TREE23_RIGHT) == NULL) {
        if (active[TREE23_LEFT] && !active[TREE23_RIGHT] &&
                add_data < this->data[TREE23_LEFT]) {
            // Left is active and less than left
            this->data[TREE23_RIGHT] = this->data[TREE23_LEFT];
            active[TREE23_RIGHT] = true;
            this->data[TREE23_LEFT] = to_add;
        } else if (active[TREE23_RIGHT] && !active[TREE23_LEFT] &&
                && add_data >= this->data[TREE23_RIGHT]) {
            // Right is active and greater than or eqaul to right
            this->data[TREE23_LEFT] = this->data[TREE23_RIGHT];
            active[TREE23_LEFT] = true;
            this->data[TREE23_RIGHT] = to_add;
        } else if (active[TREE23_RIGHT] && active[TREE23_LEFT]) {
            // Both active choose who to send up
            if (add_data < this->data[TREE23_LEFT]) {
                // Less than left, left is middle send up left
                data_type send_up = new data_type(this->data[TREE23_LEFT]);
                this->data[TREE23_LEFT] = to_add;
                return to_add;
            } else if (add_data >= this->data[TREE23_RIGHT]) {
                // Greater than or equal to the right, right is middle send up right
                data_type send_up = new data_type(this->data[TREE23_RIGHT]);
                this->data[TREE23_RIGHT] = to_add;
                return to_add;
            } else {
                // Data to add is in between left and right it is the middle so
                // send it up
                data_type send_up = new data_type(to_add);
                return to_add;
            }
        }
    } else {
        // Not a leaf node cases
        if (!active[TREE23_LEFT] && !active[TREE23_RIGHT]) {
            // Neither are active, set the left
            this->data[TREE23_LEFT] = to_add;
            active[TREE23_LEFT] = true;
        } else if (active[TREE23_LEFT] && !active[TREE23_RIGHT]) {
            // Left is active right is not
            if (add_data < this->data[TREE23_LEFT]) {
                // Left is active and less than left
                this->node(TREE23_LEFT)->add(to_add);
            } else {
                // Left is active and greater than or equal to left
                this->node(TREE23_RIGHT)->add(to_add);
            }
        } else if (active[TREE23_RIGHT] && !active[TREE23_LEFT]) {
            // Right is active left is not
            if (add_data >= this->data[TREE23_RIGHT]) {
                // Right is active and add is greater than or equal to right
                this->node(TREE23_RIGHT)->add(to_add);
            } else {
                // Right is active and add is less than right
                this->node(TREE23_LEFT)->add(to_add);
            }
        } else if (active[TREE23_RIGHT] && active[TREE23_LEFT]) {
            // Both active so we have a middle because we are not a leaf
            if (add_data < this->data[TREE23_LEFT]) {
                // Both active and less than left
                this->node(TREE23_LEFT)->add(to_add);
            } else if (add_data >= this->data[TREE23_RIGHT]) {
                // Both active and greater than or equal to right
                this->node(TREE23_RIGHT)->add(to_add);
            } else {
                // Both active and in between left and right
                this->node(TREE23_MIDDLE)->add(to_add);
            }
        }
    }
}

// Creates a node of the correct type
template <typename data_type>
bool tree23_node<data_type>::create(tree23_node_basic *& node, data_type & add_data) {
    node = new tree23_node<data_type>;
    node->data[TREE23_LEFT] = add_data;
    node->active[TREE23_LEFT] = true;
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
data_type & tree23_node<data_type>::value() {
    return data_value;
}

/*
 * Attempts to get a node at the given index and counts along the way
 */
template <typename data_type>
tree23_node_basic * tree23_node<data_type>::get_count(int & index, int & curr) {
	// To see if one of the sides found it
    tree23_node_basic * found = NULL;
	// Look of the index on the left, that will be index 0 if its the leftmost node
    if (this->node(TREE23_LEFT) != NULL) {
        found = this->node(TREE23_LEFT)->get_count(index, curr);
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
    if (this->node(TREE23_RIGHT) != NULL) {
        found = this->node(TREE23_RIGHT)->get_count(index, curr);
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
    if (this->left == NULL) {
        return false;
    }
    // If we are on the index we wish to remove then try to remove it
    if (index == curr) {
        // Store the node
        tree23_node_basic * tmp = this->left;
        // Set our left to be thenode we are removings left
        this->left = this->left->left;
        // Remove the target
        delete tmp;
        // Return true for yes we removed
        return true;
    }
    return this->left->remove_count(index, ++curr);
    */
    return true;
}
#endif
