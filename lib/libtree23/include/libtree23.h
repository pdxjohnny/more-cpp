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

#define TREE23_NUM_NODES 3

#define TREE23_LEFT 0
#define TREE23_RIGHT 1
#define TREE23_MIDDLE 2

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
        // Creates a node of the type we wish to add
        virtual bool create(tree23_node_basic *& node) = 0;
        // Get a node at an index
        virtual tree23_node_basic * get(int index);
        // Remove a node at an index returns 1 if there was a node at that index to
        // remove. Returns 0 if there was not a node at that index to remove
        virtual bool remove(int index);
        // Remove every node return the number removed
        virtual int remove_all();
        // Removes this node which will not update the node before its previous
        // and returns this nodes left node. It also sets replace to the return
        // value so you and check and set in one call
        virtual tree23_node_basic * remove_self(tree23_node_basic *& replace);
        // We need to be counting so we know what to get
        virtual tree23_node_basic * get_count(int & index, int & curr) = 0;
        // We need to be counting so we know when to remove
        virtual bool remove_count(int & index, int & curr) = 0;
    protected:
        // Lets us get the address of what this is so that we can pass by
        // refernece and still have the value
        tree23_node_basic *& as_basic();
        // Gives access to nodes
        virtual tree23_node_basic *& node(int index);
    private:
        // The left node in the list
        tree23_node_basic ** nodes;
};


/*
 * tree23_basic is a basic linked list
 */
/*
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
        tree23_node_basic * get(int index);
        // Preforms a get and if no node is present we create nodes until it is
        // present
        tree23_node_basic * get_extend(int index);
        // Calls get_extend
        tree23_node_basic * operator[](int index);
        // Removes a node from the list
        virtual bool remove(int index);
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
*/

/*
 * tree23_node is just an tree23_node_basic that holds some templated data
 */
template <typename data_type>
class tree23_node : public tree23_node_basic {
    public:
        // Constructors and Destructors
        tree23_node<data_type>();
        tree23_node<data_type>(const data_type &);
        ~tree23_node<data_type>();
        // Copies the data
        tree23_node_basic & operator=(const tree23_node_basic & copy);
        // Add a node to the tree
        tree23_node<data_type> * add(data_type & to_add);
        // Creates a node of the type we wish to add
        bool create(tree23_node_basic *& node);
        // What would should call on your root
        bool add_root(tree23_node<data_type> * root, data_type * add_data);
        // Removes this node which will not update the node before its previous
        // and returns this nodes left node. It also sets replace to the return
        // value so you and check and set in one call
        tree23_node_basic * remove_self(tree23_node_basic *& replace);
        // Return the value we are managing
        data_type & value(int index);

        bool add_root(tree23_node<data_type> * root, data_type & add_data);
        tree23_node<data_type> & set(data_type & set_to);
        tree23_node<data_type> * push_up(tree23_node<data_type> * pushed_up);

        // Returns a nodes and casts it to the correct type
        tree23_node<data_type> * node_tpl(int index);
    protected:
        // We need to be counting so we know what to get
        tree23_node_basic * get_count(int & index, int & curr);
        // We need to be counting so we know when to remove
        bool remove_count(int & index, int & curr);
    private:
        // The data we are holding
        data_type * data;
        bool * active;
};


/*
 * A liniar linked list
 */
/*
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
        data_type & operator[](int index) throw(tree23_out_of_range);
};

*/
#include "tree23_node.cpp"
// #include "tree23.cpp"
#endif
