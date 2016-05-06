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
#ifndef DLL
#define DLL 1

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <exception>

/*
 * This exception is thrown if dll cannot return the data type requested by its
 * templated value. This happens when its nodes are of a class other than
 * dll_node<data_type> * or dll_basic failed to allocate a node
 */
class dll_out_of_range : public std::exception {
    public:
        dll_out_of_range();
        ~dll_out_of_range() throw();
        virtual const char * what() const throw();
};


/*
 * The dll_node is a basic node in a dll that contains no data
 */
class dll_node_basic {
    public:
        // Constructors and Destructors
        dll_node_basic();
        dll_node_basic(const dll_node_basic & copy);
        virtual ~dll_node_basic();
        // Copy a node, not the whole list
        virtual dll_node_basic & operator=(const dll_node_basic & copy);
        // Copy the whole list
        virtual dll_node_basic & copy(const dll_node_basic & copy);
        // Add a node to the end
        virtual dll_node_basic *& add();
        // Creates a node of the type we wish to add
        virtual bool create(dll_node_basic *& node);
        // Get a node at an index
        virtual dll_node_basic * get(int index);
        // Remove a node at an index returns 1 if there was a node at that index to
        // remove. Returns 0 if there was not a node at that index to remove
        virtual bool remove(int index);
        // Remove every node return the number removed
        virtual int remove_all();
        // Removes this node which will not update the node before its previous
        // and returns this nodes next node. It also sets replace to the return
        // value so you and check and set in one call
        virtual dll_node_basic * remove_self(dll_node_basic *& replace);
    protected:
        // Lets us get the address of what this is so that we can pass by
        // refernece and still have the value
        dll_node_basic *& as_basic();
    private:
        // We need to be counting so we know what to get
        virtual dll_node_basic * get_count(int & index, int & curr);
        // We need to be counting so we know when to remove
        bool remove_count(int & index, int & curr);
        // The next node in the list
        dll_node_basic * next;
        // WOw such dll
        dll_node_basic * prev;
};


/*
 * dll_basic is a basic linked list
 */
class dll_basic {
    public:
        // Constructor and deconstructor
        dll_basic();
        dll_basic(dll_basic & copy);
        virtual ~dll_basic();
        // Copy the list
        virtual dll_basic & operator=(dll_basic & copy);
        // Adds a node to the dll
        dll_node_basic *& add();
        // What node we should create
        virtual bool create(dll_node_basic *& node);
        // Allows access by key value
        dll_node_basic * get(int index);
        // Preforms a get and if no node is present we create nodes until it is
        // present
        dll_node_basic * get_extend(int index);
        // Calls get_extend
        dll_node_basic * operator[](int index);
        // Removes a node from the list
        virtual bool remove(int index);
        // Deallocates the dll
        int remove_all();
        // Returns the number of elements in the dll
        int size();
    protected:
        // Provides the head to do operations on
        virtual dll_node_basic *& head();
    private:
        // Number of nodes in the dll
        int contains;
        // Provide us with the head to do operations on
        dll_node_basic * head_value;
};

/*
 * dll_node is just an dll_node_basic that holds some templated data
*/
template <typename data_type>
class dll_node : public dll_node_basic {
    public:
        // Constructors and Destructors
        dll_node<data_type>();
        ~dll_node<data_type>();
        // Copies the data
        dll_node_basic & operator=(const dll_node_basic & copy);
        // Allocates one of us
        bool create(dll_node_basic *& node);
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
class dll : public dll_basic {
    public:
        // Constructor and deconstructor
        dll<data_type>();
        ~dll<data_type>();
        // Allocates a dll_node and stores it in the pointer to an
        // dll_node_basic
        bool create(dll_node_basic *& node);
        // Allows access by key value and creates up to that index if it is not
        // in the list
        data_type & operator[](int index) throw(dll_out_of_range);
};

#include "dll_node.cpp"
#include "dll.cpp"
#endif
