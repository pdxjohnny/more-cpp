#include "liblll.h"
#include <libmacro.h>

/*
 * Constructor for the lll
 */
lll_basic::lll_basic() : contains(0U), head_value(NULL) {}

/*
 * Destuctor for the lll
 */
lll_basic::~lll_basic() {
    remove_all();
}

/*
 * Adds a node to the lll
 */
bool lll_basic::add(lll_node_basic *& store) {
    ++contains;
    if (this->head() == NULL) {
        if (this->create(this->head()) == false) {
            store = NULL;
            return (store != NULL);
        }
        store = this->head();
        return (store != NULL);
    }
    return this->head()->add(store);
}

/*
 * Allocates a new node, this needs to be overridden if you wish to use
 * anything other than lll_node_basic in your list
 */
bool lll_basic::create(lll_node_basic *& new_node) {
    new_node = new lll_node_basic;
    // Will be NULL if we are out of memory
    if (new_node == NULL) {
        return false;
    }
    return true;
}

/*
 * Gets a particular index in the lll
 */
bool lll_basic::get(unsigned int index, lll_node_basic *& store) {
    lll_node_basic * head_ptr = this->head();
    // Nothing to get from
    if (head_ptr == NULL) {
        store = NULL;
        return (store != NULL);
    }
    // If they want the frist one then return head
    if (index == 0U) {
        store = head_ptr;
        return (store != NULL);
    }
    // Otherwise let the nodes deal with it
    return head_ptr->get(index - 1U, store);
}

/*
 * Creates all the nodes up to index if they do not exist and returns the index
 */
bool lll_basic::get_extend(unsigned int index, lll_node_basic *& store) {
    // If we have the index in the lll then just return it
    if (index < this->size()) {
        return this->get(index, store);
    }
    // index is unsigned so the following will fail if we have nothing in the
    // list becuase i would have been -1
    // NOTE this will cause an error if contains is larger than MAX_INT or
    // MAX_UNSIGNED_INT / 2
    if (0 < (int)(this->size()) - 1) {
        return this->add(store);
    }
    // Create nodes until we have created the requested index
    unsigned int i = 0U;
    for (i = this->size(); i < index; ++i) {
        if (this->add(store) == false) {
            return false;
        }
    }
    return true;
}

/*
 * Calls get_extend
 */
lll_node_basic * lll_basic::operator[](unsigned int index) {
    lll_node_basic * store = NULL;
    this->get_extend(index, store);
    return store;
}

/*
 * Removes a particular index in the lll
 */
bool lll_basic::remove(unsigned int index) {
    lll_node_basic * head_ptr = this->head();
    // Nothing to get from
    if (head_ptr == NULL) {
        return false;
    }
    // If they want the frist one then remove the head
    if (index == 0U) {
        head_ptr->remove_self(this->head());
        return true;
    }
    // Otherwise let the nodes deal with it
    return head_ptr->remove(index);
}

/*
 * Removes all the nodes in the lll
 */
unsigned int lll_basic::remove_all() {
    lll_node_basic * head_ptr = this->head();
    // Nothing to remove
    if (head_ptr == NULL) {
        return 0;
    }
    // Remove all from the list
    unsigned int num_removed = head_ptr->remove_all();
    // Remove head
    head_ptr->remove_self(this->head());
    // We just removed the head so increment num_removed
    ++num_removed;
    // Make sure we keep track of how many wer removed
    contains -= num_removed;
    // Return how many were removed
    return num_removed;
}

/*
 * The number of elements currently in the list
 */
unsigned int lll_basic::size() {
    return contains;
}

/*
 * Returns the head nodes for functions to use
 */
lll_node_basic *& lll_basic::head() {
    return head_value;
}
