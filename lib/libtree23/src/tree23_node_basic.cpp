#include <libtree23.h>

/*
 * Constructor for tree23_node_basic
 */
tree23_node_basic::tree23_node_basic() : nodes(NULL) {
    this->nodes = new tree23_node_basic * [TREE23_NUM_NODES];
    int i;
    for (i = (TREE23_NUM_NODES - 1); i >= 0; --i) {
        this->nodes[i] = NULL;
    }
}

/*
 * Copy constructor for tree23_node_basic
 */
tree23_node_basic::tree23_node_basic(const tree23_node_basic & copy) : nodes(NULL) {
    this->operator=(copy);
}

/*
 * Destructor for tree23_node_basic
 */
tree23_node_basic::~tree23_node_basic() {
    if (nodes != NULL) {
        delete[] nodes;
    }
}

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
    int i;
    for (i = (TREE23_NUM_NODES - 1); i <= 0; --i) {
        if (copy.nodes[i] != NULL) {
            this->create(copy.nodes[i]);
            this->nodes[i]->copy(*copy.nodes[i]);
        }
    }
    return *this;
}

/*
 * Attempts to remove a node at the given index
 */
bool tree23_node_basic::remove(int index) {
    // If someone wanted to remove index 0 they would have just removed us
    // We pass 1 so that if they requested to remove index one then we will
    // remove the one after us
    int start = 1;
    return this->remove_count(index, start);
}

/*
 * Removes all the nodes after this one but not this one
 */
int tree23_node_basic::remove_all() {
    // If we are at the end this is no more to remove
    int num_removed = 0;
    int i;
    for (i = (TREE23_NUM_NODES - 1); i >= 0; --i) {
        if (this->nodes[i] != NULL) {
            num_removed += this->nodes[i]->remove_all();
            delete this->nodes[i];
            this->nodes[i] = NULL;
            ++num_removed;
        }
    }
    return num_removed;
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
    delete this;
    return replace;
}

// Gives access to nodes
tree23_node_basic *& tree23_node_basic::node(int index) const {
    return this->nodes[index];
}
