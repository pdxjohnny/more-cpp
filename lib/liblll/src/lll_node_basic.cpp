#include "liblll.h"

#ifndef LIBLLL_LLL_NODE_BAISC_METHODS
#define LIBLLL_LLL_NODE_BAISC_METHODS 1

/*
 * Constructor for lll_node_basic
 */
lll_node_basic::lll_node_basic() : next(NULL) {}

/*
 * Destructor for lll_node_basic
 */
lll_node_basic::~lll_node_basic() {}

/*
 * Adds a node to the end of the lll_basic
 */
lll_node_basic *& lll_node_basic::add() {
    if (this->next == NULL) {
        this->next = new lll_node_basic;
        return this->next;
    }
    return this->next->add();
}

/*
 * Attempts to remove a node at the given index
 */
bool lll_node_basic::remove(unsigned int index) {
    // If someone wanted to remove index 0 they would have just removed us
    // We pass 1 so that if they requested to remove index one then we will
    // remove the one after us
    unsigned int start = 1;
    return this->remove_count(index, start);
}

/*
 * Attempts to remove a node at the given index and counts along the way
 */
bool lll_node_basic::remove_count(unsigned int & index, unsigned int & curr) {
    // We want to remove the next one but we cant because there is
    // nothing to remove
    if (this->next == NULL) {
        return false;
    }
    // If we are on the index we wish to remove then try to remove it
    if (index == curr) {
        // Store the node
        lll_node_basic * tmp = this->next;
        // Set our next to be thenode we are removings next
        this->next = this->next->next;
        // Remove the target
        delete tmp;
        // Return true for yes we removed
        return true;
    }
    return this->next->remove_count(index, ++curr);
}

/*
 * Removes all the nodes after this one but not this one
 */
unsigned int lll_node_basic::remove_all() {
    // If we are at the end this is no more to remove
    if (this->next == NULL) {
        return 0;
    }
    unsigned int num_removed = this->next->remove_all();
    delete this->next;
    this->next = NULL;
    return 1 + num_removed;
}

#endif
