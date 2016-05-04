#include "liblll.h"
#include <libmacro.h>

/*
 * Constructor for the lll
 */
lll_basic::lll_basic() : contains(0), head_value(NULL) {}

/*
 * Destuctor for the lll
 */
lll_basic::~lll_basic() {
    remove_all();
}

/*
 * Adds a node to the lll
 */
lll_node_basic *& lll_basic::add() {
    ++contains;
    if (this->head() == NULL) {
        this->create(this->head());
        return this->head();
    }
    return this->head()->add();
}

/*
 * Allocates a node, this needs to be overridden if you wish to use
 * anything other than lll_node_basic in your list
 */
bool lll_basic::create(lll_node_basic *& node) {
    node = new lll_node_basic;
    // Will be NULL if we are out of memory
    return (node != NULL);
}

/*
 * Gets a particular index in the lll
 */
lll_node_basic * lll_basic::get(int index) {
    lll_node_basic * head_ptr = this->head();
    // Nothing to get from
    if (head_ptr == NULL) {
        return NULL;
    }
    // Otherwise let the nodes deal with it
    return head_ptr->get(index);
}

/*
 * Creates all the nodes up to index if they do not exist and returns the index
 */
lll_node_basic * lll_basic::get_extend(int index) {
    // The node to return
    lll_node_basic * to_ret = NULL;
    // If we have the index in the lll then just return it
    if (index < this->size()) {
        return this->get(index);
    }
    // Create nodes until we have created the requested index
    int i = 0;
    for (i = this->size(); i <= index; ++i) {
        to_ret = this->add();
    }
    return to_ret;
}

/*
 * Calls get_extend
 */
lll_node_basic * lll_basic::operator[](int index) {
    return this->get_extend(index);
}

/*
 * Removes a particular index in the lll
 */
bool lll_basic::remove(int index) {
    lll_node_basic * head_ptr = this->head();
    // Nothing to get from
    if (head_ptr == NULL) {
        return false;
    }
    // If they want the frist one then remove the head
    if (index == 0) {
        head_ptr->remove_self(this->head());
        return true;
    }
    // Otherwise let the nodes deal with it
    return head_ptr->remove(index);
}

/*
 * Removes all the nodes in the lll
 */
int lll_basic::remove_all() {
    lll_node_basic * head_ptr = this->head();
    // Nothing to remove
    if (head_ptr == NULL) {
        return 0;
    }
    // Remove all from the list
    int num_removed = head_ptr->remove_all();
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
int lll_basic::size() {
    return contains;
}

/*
 * Returns the head nodes for functions to use
 */
lll_node_basic *& lll_basic::head() {
    return head_value;
}
