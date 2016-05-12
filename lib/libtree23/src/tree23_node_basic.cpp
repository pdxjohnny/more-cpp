#include <libtree23.h>

/*
 * Constructor for tree23_node_basic
 */
tree23_node_basic::tree23_node_basic() : left(NULL), right(NULL) {}

/*
 * Copy constructor for tree23_node_basic
 */
tree23_node_basic::tree23_node_basic(const tree23_node_basic & copy) : left(NULL), right(NULL) {
    this->operator=(copy);
}

/*
 * Destructor for tree23_node_basic
 */
tree23_node_basic::~tree23_node_basic() {}

/*
 * Copy a node, not the whole list
 */
tree23_node_basic & tree23_node_basic::operator=(const tree23_node_basic & copy) {
    return *this;
}

/*
 * Copy the whole list
 */
tree23_node_basic & tree23_node_basic::copy(const tree23_node_basic & copy) {
    // Copy what we hold
    this->operator=(copy);
    // This is all there is to copy
    if (copy.left == NULL && copy.right == NULL) {
        return *this;
    }
    // There is more to copy
    if (copy.left != NULL) {
        this->create(this->left);
        this->left->copy(*copy.left);
    }
    if (copy.right != NULL) {
        this->create(this->right);
        this->right->copy(*copy.right);
    }
    return *this;
}

/*
 * Adds a node to the end of the tree23_basic
 */
tree23_node_basic *& tree23_node_basic::add() {
    if (this->left == NULL) {
        this->create(this->left);
        return this->left;
    }
    return this->left->add();
}

/*
 * Allocates a node and returns true on succesfull allocation
 */
bool tree23_node_basic::create(tree23_node_basic *& node) {
    node = new tree23_node_basic;
    // Will be NULL if we are out of memory
    return (node != NULL);
}

/*
 * Attempts to retrive a node at the given index
 */
tree23_node_basic * tree23_node_basic::get(const char * key) {
    int start = 0;
    return this->get_count(index, start);
}

/*
 * Attempts to get a node at the given index and counts along the way
 */
tree23_node_basic * tree23_node_basic::get_count(int & index, int & curr) {
    // If we are on the index we wish to get then return ourself
    if (index == curr) {
        return this;
    }
    // We want to get the left one but we cant because there is
    // nothing to get
    if (this->left == NULL) {
        return NULL;
    }
    return this->left->get_count(index, ++curr);
}

/*
 * Attempts to remove a node at the given index
 */
bool tree23_node_basic::remove(const char * key) {
    // If someone wanted to remove index 0 they would have just removed us
    // We pass 1 so that if they requested to remove index one then we will
    // remove the one after us
    int start = 1;
    return this->remove_count(index, start);
}

/*
 * Attempts to remove a node at the given index and counts along the way
 */
bool tree23_node_basic::remove_count(int & index, int & curr) {
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
}

/*
 * Removes all the nodes after this one but not this one
 */
int tree23_node_basic::remove_all() {
    // If we are at the end this is no more to remove
    if (this->left == NULL) {
        return 0;
    }
    int num_removed = this->left->remove_all();
    delete this->left;
    this->left = NULL;
    return 1 + num_removed;
}

/*
 * If remove self is called the caller needs to be aware that this does not
 * update the left pointer of the node previous to this one and will break the
 * list. If this is the root pointer then that doesnt matter because there is
 * no previous poitner. However if you have the pointer previous to this it is
 * preferable to all the remove(index) function so that the left poitners of
 * the tree23 will be updated correctly
 */
tree23_node_basic * tree23_node_basic::remove_self(tree23_node_basic *& replace) {
    replace = this->left;
    delete this;
    return replace;
}
