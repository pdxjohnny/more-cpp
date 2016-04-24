#include <cstdlib>

#include <libmacro.h>

#define CIRCLE_HERE 1
#define CIRCLE_NEXT 2

class circle {
public:
    circle();
    // Add to another node
    circle(circle * existing);
    virtual ~circle();
    circle & operator=(const circle & copy);
    // Remove me and return the next
    circle * bump();
    // Distroy all in the list
    void destroy();
    // These need to be implimented by children of this base class
    virtual char match(circle *) = 0;
    virtual char sort(circle *) = 0;
    // Add a node this nodes list
    circle * add(circle *);
    circle * add_node(circle *);
    // Find a node in the list
    circle * get(circle *);
    circle * find_match(circle *);
    // Remove a node from the list, get and delete
    char remove(circle *);
    // To make sure that the list is in the order of this array
    int test_order(circle ** match_these);
    // Do something to each node, return something other than EXIT_SUCCESS if
    // you wish to stop, you must implement do_func within circle::each
    class each;
    int oneach(circle::each & each_class);
private:
    // Set the new head
    void update_head(circle * set_to);
    circle * head;
    circle * next;
    circle * prev;
};

class circle::each {
public:
    virtual int do_func(circle *) = 0;
};
