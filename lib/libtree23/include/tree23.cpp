#include "libtree23.h"
#include <libmacro.h>

#ifndef LIBTREE23_TREE23
#define LIBTREE23_TREE23

// Constructor
template <typename data_type>
tree23<data_type>::tree23() : contains(0), data(NULL), active(NULL) {
    data = new data_type [2];
    active = new bool [2];
    active[TREE23_LEFT] = false;
    active[TREE23_RIGHT] = false;
}

// Constructor
template <typename data_type>
tree23<data_type>::tree23(const data_type & set_to) : contains(0), data(NULL), active(NULL) {
    data = new data_type [2];
    active = new bool [2];
    active[TREE23_RIGHT] = false;
    active[TREE23_LEFT] = true;
    data[TREE23_LEFT] = set_to;
}

// Destructor
template <typename data_type>
tree23<data_type>::~tree23() {
    if (active != NULL) {
        delete[] active;
    }
    if (data != NULL) {
        delete[] data;
    }
}

// Copies the data of the node
template <typename data_type>
tree23<data_type> & tree23<data_type>::operator=(const tree23<data_type> & copy) {
    tree23_basic::operator=(copy);
    return *this;
}

// Copies the data of the node
template <typename data_type>
void tree23<data_type>::copy(const tree23_basic & copy) {
    const tree23<data_type> * copy_ptr = dynamic_cast<const tree23<data_type> *>(&copy);
    // Nothing to copy or bad typecast
    if (copy_ptr == NULL) {
        return;
    }
    if (this == copy_ptr) {
        return;
    }
    contains = copy_ptr->contains;
    if (copy_ptr->data != NULL) {
        data[TREE23_LEFT] = copy_ptr->data[TREE23_LEFT];
        data[TREE23_RIGHT] = copy_ptr->data[TREE23_RIGHT];
    }
    if (copy_ptr->active != NULL) {
        active[TREE23_LEFT] = copy_ptr->active[TREE23_LEFT];
        active[TREE23_RIGHT] = copy_ptr->active[TREE23_RIGHT];
    }
    return;
}

// Calls add
template <typename data_type>
tree23<data_type> & tree23<data_type>::operator+=(const data_type & to_add) {
    add(to_add);
    return *this;
}

// Adds a node to the end of the tree23_basic
template <typename data_type>
tree23<data_type> * tree23<data_type>::add(const data_type & to_add) {
    ++contains;
    tree23<data_type> * send_up = NULL;
    // Neither are active, set the left
    if (!active[TREE23_LEFT] && !active[TREE23_RIGHT]) {
        data[TREE23_LEFT] = to_add;
        active[TREE23_LEFT] = true;
    } else if (node(TREE23_LEFT) == NULL && node(TREE23_MIDDLE) == NULL &&
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
            send_up = this;
            // Both active choose who to send up
            if (to_add < data[TREE23_LEFT]) {
                // Less than left, left is middle send up left
                node(TREE23_LEFT) = new tree23(to_add);
                node(TREE23_RIGHT) = new tree23(data[TREE23_RIGHT]);
                active[TREE23_RIGHT] = false;
            } else if (to_add >= data[TREE23_RIGHT]) {
                // Greater than or equal to the right, right is middle send up right
                node(TREE23_LEFT) = new tree23(data[TREE23_LEFT]);
                node(TREE23_RIGHT) = new tree23(to_add);
                set(data[TREE23_RIGHT]);
            } else {
                // Data to add is in between left and right it is the middle so
                // send it up
                node(TREE23_LEFT) = new tree23(data[TREE23_LEFT]);
                node(TREE23_RIGHT) = new tree23(data[TREE23_RIGHT]);
                set(to_add);
            }
        }
    } else {
        if (active[TREE23_LEFT] && !active[TREE23_RIGHT]) {
            // Left is active right is not
            if (to_add < data[TREE23_LEFT]) {
                // Left is active and less than left
                send_up = push_up(node_tpl(TREE23_LEFT)->add(to_add));
            } else {
                // Left is active and greater than or equal to left
                send_up = push_up(node_tpl(TREE23_RIGHT)->add(to_add));
            }
        } else if (active[TREE23_RIGHT] && active[TREE23_LEFT]) {
            // Both active so we have a middle because we are not a leaf
            if (to_add < data[TREE23_LEFT]) {
                // Both active and less than left
                send_up = push_up(node_tpl(TREE23_LEFT)->add(to_add));
            } else if (to_add >= data[TREE23_RIGHT]) {
                // Both active and greater than or equal to right
                send_up = push_up(node_tpl(TREE23_RIGHT)->add(to_add));
            } else {
                // Both active and in between left and right
                send_up = push_up(node_tpl(TREE23_MIDDLE)->add(to_add));
            }
        }
    }
    return send_up;
}

// If add returns a node then it is pushing that node up. This handles the
// pushing up of a node
template <typename data_type>
bool tree23<data_type>::add_root(tree23<data_type> * root, data_type & add_data) {
    push_up(add(add_data));
    return true;
}

// Sets the left to the data and marks the right as inactive
template <typename data_type>
tree23<data_type> & tree23<data_type>::set(const data_type & set_to) {
    data[TREE23_LEFT] = set_to;
    active[TREE23_LEFT] = true;
    active[TREE23_RIGHT] = false;
    return *this;
}

// If add returns a node then it is pushing that node up. This handles the
// pushing up of a node
template <typename data_type>
tree23<data_type> * tree23<data_type>::push_up(tree23<data_type> * pushed_up) {
    tree23<data_type> * send_up = NULL;
    // Nothing pushed up
    if (pushed_up == NULL) {
        return send_up;
    }
    if (this == pushed_up) {
        return NULL;
    }
    // If the child was full and I am full
    if (active[TREE23_RIGHT] && active[TREE23_LEFT]) {
        send_up = this;
        // Both active choose who to send up
        if (pushed_up->data[TREE23_LEFT] < data[TREE23_LEFT]) {
            // Less than left, left is middle send up left
            tree23 * new_right = new tree23(data[TREE23_RIGHT]);
            new_right->node(TREE23_RIGHT) = node(TREE23_RIGHT);
            new_right->node(TREE23_LEFT) = node(TREE23_MIDDLE);
            active[TREE23_RIGHT] = false;
            node(TREE23_LEFT) = pushed_up;
            node(TREE23_RIGHT) = new_right;
            node(TREE23_MIDDLE) = NULL;
        } else if (pushed_up->data[TREE23_LEFT] >= data[TREE23_RIGHT]) {
            // Greater than or equal to the right, right is middle send up right
            tree23 * new_left = new tree23(data[TREE23_LEFT]);
            new_left->node(TREE23_LEFT) = node(TREE23_LEFT);
            new_left->node(TREE23_RIGHT) = node(TREE23_MIDDLE);
            set(data[TREE23_RIGHT]);
            node(TREE23_LEFT) = new_left;
            node(TREE23_RIGHT) = pushed_up;
            node(TREE23_MIDDLE) = NULL;
        } else {
            // Data to add is in between left and right it is the middle so
            // send it up
            tree23 * new_left = new tree23(data[TREE23_LEFT]);
            tree23 * new_right = new tree23(data[TREE23_RIGHT]);
            new_left->node(TREE23_LEFT) = node(TREE23_LEFT);
            new_left->node(TREE23_RIGHT) = pushed_up->node(TREE23_LEFT);
            new_right->node(TREE23_RIGHT) = node(TREE23_RIGHT);
            new_right->node(TREE23_LEFT) = pushed_up->node(TREE23_RIGHT);
            set(pushed_up->data[TREE23_LEFT]);
            node(TREE23_LEFT) = new_left;
            node(TREE23_RIGHT) = new_right;
            node(TREE23_MIDDLE) = NULL;
        }
    // Data pushed up goes into the left spot
    } else if (pushed_up->data[TREE23_LEFT] < data[TREE23_LEFT]) {
        active[TREE23_RIGHT] = true;
        data[TREE23_RIGHT] = data[TREE23_LEFT];
        data[TREE23_LEFT] = pushed_up->data[TREE23_LEFT];
        node(TREE23_LEFT) = pushed_up->node(TREE23_LEFT);
        node(TREE23_MIDDLE) = pushed_up->node(TREE23_RIGHT);
        delete pushed_up;
    // Data pushed up goes in the right spot
    } else {
        active[TREE23_RIGHT] = true;
        data[TREE23_RIGHT] = pushed_up->data[TREE23_LEFT];
        node(TREE23_RIGHT) = pushed_up->node(TREE23_RIGHT);
        node(TREE23_MIDDLE) = pushed_up->node(TREE23_LEFT);
        delete pushed_up;
    }
    return send_up;
}

// Creates a node of the correct type
template <typename data_type>
bool tree23<data_type>::create(tree23_basic *& node) {
    tree23 * tmp = new tree23<data_type>;
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
tree23_basic * tree23<data_type>::remove_self(tree23_basic *& replace) {
    delete this;
    return replace;
}

// Return the value we are managing
template <typename data_type>
data_type & tree23<data_type>::value(int index) {
    return data[index];
}

/*
 * Attempts to get a node at the given index and counts along the way
 */
template <typename data_type>
data_type & tree23<data_type>::get_count(int & index, int & curr) const {
	// To see if one of the sides found it
    data_type * found = NULL;
	// Look of the index on the left, that will be index 0 if its the leftmost node
    if (node(TREE23_LEFT) != NULL) {
        try {
            found = &node_tpl(TREE23_LEFT)->get_count(index, curr);
            return *found;
        } catch (tree23_out_of_range err) {
            // pass
        }
    }
	// Check if this node is the index
    if (active[TREE23_LEFT]) {
        if (index == curr) {
            return data[TREE23_LEFT];
        }
        // increment the index
        ++curr;
    }
	// Look of the index down the middle
    if (node(TREE23_MIDDLE) != NULL) {
        try {
            found = &node_tpl(TREE23_MIDDLE)->get_count(index, curr);
            return *found;
        } catch (tree23_out_of_range err) {
            // pass
        }
    }
	// Check if this node is the index
    if (active[TREE23_RIGHT]) {
        if (index == curr) {
            return data[TREE23_RIGHT];
        }
        // increment the index
        ++curr;
    }
	// Look of the index on the right
    if (node(TREE23_RIGHT) != NULL) {
        try {
            found = &node_tpl(TREE23_RIGHT)->get_count(index, curr);
            return *found;
        } catch (tree23_out_of_range err) {
            // pass
        }
    }
    throw(tree23_out_of_range());
}

/*
 * Attempts to remove a node at the given index and counts along the way
 */
template <typename data_type>
bool tree23<data_type>::remove_count(int & index, int & curr) {
    /*
    // We want to remove the left one but we cant because there is
    // nothing to remove
    if (left == NULL) {
        return false;
    }
    // If we are on the index we wish to remove then try to remove it
    if (index == curr) {
        // Store the node
        tree23_basic * tmp = left;
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

template <typename data_type>
tree23<data_type> * tree23<data_type>::node_tpl(int index) const {
    return dynamic_cast<tree23<data_type> *>(tree23_basic::node(index));
}

template <typename data_type>
data_type & tree23<data_type>::operator[](int index) const throw(tree23_out_of_range) {
    int curr = 0;
    return get_count(index, curr);
}

// Displays everything in the tree
template <typename data_type>
void tree23<data_type>::display(std::ostream & out) const {
    int i = contains;
    for (i = contains - 1; i >= 0; --i) {
        out << operator[](i) << std::endl;
    }
    return;
}

// Calls display
template <typename data_type>
std::ostream & operator << (std::ostream & out, const tree23<data_type> & tree) {
    tree.display(out);
    return out;
}

// Returns contains
template <typename data_type>
int tree23<data_type>::size() const{
    return contains;
}
#endif
