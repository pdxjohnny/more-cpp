#include <liblll.h>

/*
 * Constructor for lll_node_basic
 */
lll_node_basic::lll_node_basic() : next(NULL) {}

/*
 * Copy constructor for lll_node_basic
 */
lll_node_basic::lll_node_basic(const lll_node_basic & copy) : next(NULL) {
    this->operator=(copy);
}

/*
 * Destructor for lll_node_basic
 */
lll_node_basic::~lll_node_basic() {}

/*
 * Copy a node, not the whole list
 */
lll_node_basic & lll_node_basic::operator=(const lll_node_basic & copy) {
    return *this;
}

/*
 * Copy the whole list
 */
lll_node_basic & lll_node_basic::copy(const lll_node_basic & copy) {
    // Copy what we hold
    this->operator=(copy);
    // This is all there is to copy
    if (copy.next == NULL) {
        return *this;
    }
    // There is more to copy
    this->create(this->next);
    this->next->copy(*copy.next);
    return *this;
}

/*
 * Adds a node to the end of the lll_basic
 */
lll_node_basic *& lll_node_basic::add() {
    if (this->next == NULL) {
        this->create(this->next);
        return this->next;
    }
    return this->next->add();
}

/*
 * Allocates a node and returns true on succesfull allocation
 */
bool lll_node_basic::create(lll_node_basic *& node) {
    node = new lll_node_basic;
    // Will be NULL if we are out of memory
    return (node != NULL);
}

/*
 * Attempts to retrive a node at the given index
 */
lll_node_basic * lll_node_basic::get(int index) {
    int start = 0;
    return this->get_count(index, start);
}

/*
 * Attempts to get a node at the given index and counts along the way
 */
lll_node_basic * lll_node_basic::get_count(int & index, int & curr) {
    // If we are on the index we wish to get then return ourself
    if (index == curr) {
        return this;
    }
    // We want to get the next one but we cant because there is
    // nothing to get
    if (this->next == NULL) {
        return NULL;
    }
    return this->next->get_count(index, ++curr);
}

/*
 * Attempts to remove a node at the given index
 */
bool lll_node_basic::remove(int index) {
    // If someone wanted to remove index 0 they would have just removed us
    // We pass 1 so that if they requested to remove index one then we will
    // remove the one after us
    int start = 1;
    return this->remove_count(index, start);
}

/*
 * Attempts to remove a node at the given index and counts along the way
 */
bool lll_node_basic::remove_count(int & index, int & curr) {
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
int lll_node_basic::remove_all() {
    // If we are at the end this is no more to remove
    if (this->next == NULL) {
        return 0;
    }
    int num_removed = this->next->remove_all();
    delete this->next;
    this->next = NULL;
    return 1 + num_removed;
}

/*
 * If remove self is called the caller needs to be aware that this does not
 * update the next pointer of the node previous to this one and will break the
 * list. If this is the head pointer then that doesnt matter because there is
 * no previous poitner. However if you have the pointer previous to this it is
 * preferable to all the remove(index) function so that the next poitners of
 * the lll will be updated correctly
 */
lll_node_basic * lll_node_basic::remove_self(lll_node_basic *& replace) {
    replace = this->next;
    delete this;
    return replace;
}
