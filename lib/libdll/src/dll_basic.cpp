#include <libdll.h>

/*
 * Constructor for the dll
 */
dll_basic::dll_basic() : contains(0), head_value(NULL) {}

/*
 * Copies one dll to another, cant use const because of head()
 */
dll_basic::dll_basic(dll_basic & copy) : contains(0), head_value(NULL) {
    this->operator=(copy);
}

/*
 * Destuctor for the dll
 */
dll_basic::~dll_basic() {
    remove_all();
}

/*
 * Copy the whole list, cant use const beacuse of head()
 */
dll_basic & dll_basic::operator=(dll_basic & copy) {
    // Remove all nodes from this list
    this->remove_all();
    // Must call the method with a pointer to have the virtual fucniton invoked
    dll_basic * copy_virtual = &copy;
    if (copy_virtual->head() == NULL) {
        return *this;
    }
    if (this->head() == NULL) {
        this->create(this->head());
    }
    this->head()->copy(*(copy_virtual->head()));
    this->contains = copy.contains;
    return *this;
}

/*
 * Adds a node to the dll
 */
dll_node_basic *& dll_basic::add() {
    ++contains;
    if (this->head() == NULL) {
        this->create(this->head());
        return this->head();
    }
    return this->head()->add();
}

/*
 * Allocates a node, this needs to be overridden if you wish to use
 * anything other than dll_node_basic in your list
 */
bool dll_basic::create(dll_node_basic *& node) {
    node = new dll_node_basic;
    // Will be NULL if we are out of memory
    return (node != NULL);
}

/*
 * Gets a particular index in the dll
 */
dll_node_basic * dll_basic::get(int index) {
    dll_node_basic * head_ptr = this->head();
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
dll_node_basic * dll_basic::get_extend(int index) {
    // The node to return
    dll_node_basic * to_ret = NULL;
    // If we have the index in the dll then just return it
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
dll_node_basic * dll_basic::operator[](int index) {
    return this->get_extend(index);
}

/*
 * Removes a particular index in the dll
 */
bool dll_basic::remove(int index) {
    dll_node_basic * head_ptr = this->head();
    // Nothing to get from
    if (head_ptr == NULL) {
        return false;
    }
    // If they want the frist one then remove the head
    if (index == 0) {
        head_ptr->remove_self(this->head());
        --contains;
        return true;
    }
    // Otherwise let the nodes deal with it
    bool removed = head_ptr->remove(index);
    if (removed == true) {
        --contains;
    }
    return removed;
}

/*
 * Removes all the nodes in the dll
 */
int dll_basic::remove_all() {
    dll_node_basic * head_ptr = this->head();
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
int dll_basic::size() {
    return contains;
}

/*
 * Returns the head nodes for functions to use
 */
dll_node_basic *& dll_basic::head() {
    return head_value;
}
