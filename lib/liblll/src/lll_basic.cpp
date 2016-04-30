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
lll_node_basic *& lll_basic::add() {
    if (head() == NULL) {
        create(head());
        return head();
    }
    return head()->add();
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
lll_node_basic * lll_basic::get(unsigned int index) {
    lll_node_basic * head_ptr = head();
    // Nothing to get from
    if (head_ptr == NULL) {
        return NULL;
    }
    // If they want the frist one then return head
    if (index == 0U) {
        return head_ptr;
    }
    // Otherwise let the nodes deal with it
    return head_ptr->get(index);
}

/*
 * Removes a particular index in the lll
 */
bool lll_basic::remove(unsigned int index) {
    lll_node_basic * head_ptr = head();
    MACRO_LOG_POINTER(head_ptr);
    // Nothing to get from
    if (head_ptr == NULL) {
        return false;
    }
    // If they want the frist one then remove the head
    if (index == 0U) {
        head_ptr->remove_self(head());
        MACRO_LOG_STR("Returning true");
        return true;
    }
    // Otherwise let the nodes deal with it
    return head_ptr->remove(index);
}

/*
 * Removes all the nodes in the lll
 */
unsigned int lll_basic::remove_all() {
    lll_node_basic * head_ptr = head();
    // Nothing to remove
    if (head_ptr == NULL) {
        return 0;
    }
    // Remove all from the list
    unsigned int num_removed = head_ptr->remove_all();
    // Remove head
    head_ptr->remove_self(head());
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
