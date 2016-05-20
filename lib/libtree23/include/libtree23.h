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

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <exception>

/*
 * This exception is thrown if tree23 cannot return the data type requested by its
 * templated value. This happens when its nodes are of a class other than
 * tree23<data_type> * or tree23_basic failed to allocate a node
 */
class tree23_out_of_range : public std::exception {
    public:
        tree23_out_of_range();
        ~tree23_out_of_range() throw();
        virtual const char * what() const throw();
};


/*
 * The tree23 is a basic node in a tree23 that contains no data
 */
class tree23_basic {
    public:
        // Constructors and Destructors
        tree23_basic();
        tree23_basic(const tree23_basic & copy);
        virtual ~tree23_basic();
        // Copy the whole list
        virtual tree23_basic & operator=(const tree23_basic & copy);
        // Copy a node, not the whole list
        virtual void copy(const tree23_basic & copy) = 0;
        // Creates a node of the type we wish to add
        virtual bool create(tree23_basic *& node) = 0;
        // Remove a node at an index returns 1 if there was a node at that index to
        // remove. Returns 0 if there was not a node at that index to remove
        virtual bool remove(int index);
        // Remove every node return the number removed
        virtual int remove_all();
        // Removes this node which will not update the node before its previous
        // and returns this nodes left node. It also sets replace to the return
        // value so you and check and set in one call
        virtual tree23_basic * remove_self(tree23_basic *& replace);
        // We need to be counting so we know when to remove
        virtual bool remove_count(int & index, int & curr) = 0;
    protected:
        // Lets us get the address of what this is so that we can pass by
        // refernece and still have the value
        tree23_basic *& as_basic();
        // Gives access to nodes
        virtual tree23_basic *& node(int index) const;
    private:
        // The left node in the list
        tree23_basic ** nodes;
};

/*
 * tree23 is just an tree23_basic that holds some templated data
 */
template <typename data_type>
class tree23 : public tree23_basic {
    public:
        // Constructors and Destructors
        tree23<data_type>();
        tree23<data_type>(const data_type &);
        ~tree23<data_type>();
        // Cpoies the wholel list
        tree23 & operator=(const tree23 & copy);
        // Copies the data of the node
        void copy(const tree23_basic & copy);
        // Calls add
        tree23<data_type> & operator+=(const data_type & to_add);
        // Add a node to the tree
        tree23<data_type> * add(const data_type & to_add);
        // Creates a node of the type we wish to add
        bool create(tree23_basic *& node);
        // What would should call on your root
        bool add_root(tree23<data_type> * root, data_type * add_data);
        // Removes this node which will not update the node before its previous
        // and returns this nodes left node. It also sets replace to the return
        // value so you and check and set in one call
        tree23_basic * remove_self(tree23_basic *& replace);
        // Return the value we are managing
        data_type & value(int index);

        bool add_root(tree23<data_type> * root, data_type & add_data);
        tree23<data_type> & set(const data_type & set_to);
        tree23<data_type> * push_up(tree23<data_type> * pushed_up);

        // Returns a nodes and casts it to the correct type
        tree23<data_type> * node_tpl(int index) const;

        // Access like a sorted array
        data_type & operator[](int index) const throw(tree23_out_of_range);

        // Display everything in the tree
        virtual void display(std::ostream & out);
        template <typename data_type_2>
        friend std::ostream & operator >> (std::ostream &, const tree23<data_type_2> &);
        // Returns the size
        int size() const;
    protected:
        // We need to be counting so we know what to get
        data_type & get_count(int & index, int & curr) const;
        // We need to be counting so we know when to remove
        bool remove_count(int & index, int & curr);
    private:
        // Number of times add has been called
        int contains;
        // The data we are holding
        data_type * data;
        bool * active;
};

#include "tree23.cpp"
#endif
