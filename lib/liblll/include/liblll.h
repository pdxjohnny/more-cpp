/*
    Author: John Andersen
    Date: 04/28/2015
    Description: Linear Linked List
*/

// For NULL
#ifndef NULL
    #define NULL 0
#endif

// Ensure nothing gets redeclared
#ifndef LLL
#define LLL 1

#include <cstdio>
#include <cstdlib>
#include <cstring>

/*
 * The lll_node is a basic node in a lll that contains no data
 */
class lll_node_basic {
    public:
        // Constructors and Destructors
        lll_node_basic();
        virtual ~lll_node_basic();
        // Add a node to the end
        virtual lll_node_basic *& add();
        // Creates a node of the type we wish to add, new is set to new_node
        virtual bool create(lll_node_basic *& new_node);
        // Get a node at an index
        virtual lll_node_basic * get(unsigned int index);
        // Remove a node at an index returns 1 if there was a node at that index to
        // remove. Returns 0 if there was not a node at that index to remove
        virtual bool remove(unsigned int index);
        // Remove every node return the number removed
        virtual unsigned int remove_all();
        // Removes this node which will not update the node before its previous
        // and returns this nodes next node. It also sets replace to the return
        // value so you and check and set in one call
        virtual lll_node_basic * remove_self(lll_node_basic *& replace);
    private:
        // We need to be counting so we know what to get
        virtual lll_node_basic * get_count(unsigned int & index, unsigned int & curr);
        // We need to be counting so we know when to remove
        bool remove_count(unsigned int & index, unsigned int & curr);
        // The next node in the list
        lll_node_basic * next;
};


/*
 * lll_basic is a basic linked list
 */
class lll_basic {
    public:
        // Constructor and deconstructor
        lll_basic();
        virtual ~lll_basic();
        // Adds a node to the lll
        lll_node_basic *& add();
        // What node we should create
        virtual bool create(lll_node_basic *& new_node);
        // Allows access by key value
        lll_node_basic * get(unsigned int index);
        // Removes a node from the list
        bool remove(unsigned int index);
        // Deallocates the lll
        unsigned int remove_all();
        // Returns the number of elements in the lll
        unsigned int size();
    protected:
        // Provides the head to do operations on
        lll_node_basic *& head();
    private:
        // Number of nodes in the lll
        unsigned int contains;
        // Provide us with the head to do operations on
        lll_node_basic * head_value;
};

/*
 * lll_node is just an lll_node_basic that holds some templated data
*/
template <typename data_type>
class lll_node : public lll_node_basic {
    public:
        // Constructors and Destructors
        lll_node<data_type>();
        ~lll_node<data_type>();
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
class lll : public lll_basic {
    public:
        // Constructor and deconstructor
        lll<data_type>();
        ~lll<data_type>();
        // Allows access by key value
        data_type & operator [] (unsigned int index);
    protected:
        // So the lll_basic can access our head
        lll_node<data_type> *& head();
    private:
        // Head of the lll
        lll_node<data_type> * head_value;
};


#include "lll_node.cpp"
#include "lll.cpp"
#endif
