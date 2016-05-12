/*
    Author: John Andersen
    Date: 05/09/2016
    Description: Binary search tree
*/

// For NULL
#ifndef NULL
    #define NULL 0U
#endif

// Ensure nothing gets redeclared
#ifndef TREE23
#define TREE23 1

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <exception>

/*
 * This exception is thrown if tree23 cannot return the data type requested by its
 * templated value. This happens when its nodes are of a class other than
 * tree23_node<data_type> * or tree23_basic failed to allocate a node
 */
class tree23_out_of_range : public std::exception {
    public:
        tree23_out_of_range();
        ~tree23_out_of_range() throw();
        virtual const char * what() const throw();
};


/*
 * The tree23_node is a basic node in a tree23 that contains no data
 */
class tree23_node_basic {
    public:
        // Constructors and Destructors
        tree23_node_basic();
        tree23_node_basic(const tree23_node_basic & copy);
        virtual ~tree23_node_basic();
        // Copy a node, not the whole list
        virtual tree23_node_basic & operator=(const tree23_node_basic & copy);
        // Copy the whole list
        virtual tree23_node_basic & copy(const tree23_node_basic & copy);
        // Add a node to the end
        virtual tree23_node_basic *& add();
        // Creates a node of the type we wish to add
        virtual bool create(tree23_node_basic *& node);
        // Get a node at an index
        virtual tree23_node_basic * get(const char * key);
        // Remove a node at an index returns 1 if there was a node at that index to
        // remove. Returns 0 if there was not a node at that index to remove
        virtual bool remove(const char * key);
        // Remove every node return the number removed
        virtual int remove_all();
        // Removes this node which will not update the node before its previous
        // and returns this nodes left node. It also sets replace to the return
        // value so you and check and set in one call
        virtual tree23_node_basic * remove_self(tree23_node_basic *& replace);
    protected:
        // Lets us get the address of what this is so that we can pass by
        // refernece and still have the value
        tree23_node_basic *& as_basic();
    private:
        // We need to be counting so we know what to get
        virtual tree23_node_basic * get_count(int & index, int & curr);
        // We need to be counting so we know when to remove
        bool remove_count(int & index, int & curr);
        // The left node in the list
        tree23_node_basic * left;
};


/*
 * tree23_basic is a basic linked list
 */
class tree23_basic {
    public:
        // Constructor and deconstructor
        tree23_basic();
        tree23_basic(tree23_basic & copy);
        virtual ~tree23_basic();
        // Copy the list
        virtual tree23_basic & operator=(tree23_basic & copy);
        // Adds a node to the tree23
        tree23_node_basic *& add();
        // What node we should create
        virtual bool create(tree23_node_basic *& node);
        // Allows access by key value
        tree23_node_basic * get(const char * key);
        // Preforms a get and if no node is present we create nodes until it is
        // present
        tree23_node_basic * get_extend(const char * key);
        // Calls get_extend
        tree23_node_basic * operator[](const char * key);
        // Removes a node from the list
        virtual bool remove(const char * key);
        // Deallocates the tree23
        int remove_all();
        // Returns the number of elements in the tree23
        int size();
    protected:
        // Provides the root to do operations on
        virtual tree23_node_basic *& root();
    private:
        // Number of nodes in the tree23
        int contains;
        // Provide us with the root to do operations on
        tree23_node_basic * root_value;
};

/*
 * tree23_node is just an tree23_node_basic that holds some templated data
*/
template <typename data_type>
class tree23_node : public tree23_node_basic {
    public:
        // Constructors and Destructors
        tree23_node<data_type>();
        ~tree23_node<data_type>();
        // Copies the data
        tree23_node_basic & operator=(const tree23_node_basic & copy);
        // Allocates one of us
        bool create(tree23_node_basic *& node);
        // Return the value we are managing
        data_type & value();
    private:
        // The data we are holding
        data_type data_value;
};


/*
 * A liniar linked list
 */
template <typename data_type>
class tree23 : public tree23_basic {
    public:
        // Constructor and deconstructor
        tree23<data_type>();
        ~tree23<data_type>();
        // Allocates a tree23_node and stores it in the pointer to an
        // tree23_node_basic
        bool create(tree23_node_basic *& node);
        // Allows access by key value and creates up to that index if it is not
        // in the list
        data_type & operator[](const char * key) throw(tree23_out_of_range);
};

#include "tree23_node.cpp"
#include "tree23.cpp"
#endif
