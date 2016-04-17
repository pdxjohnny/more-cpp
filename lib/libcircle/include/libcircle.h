#include <cstdlib>

#include <libmacro.h>

#define CIRCLE_HERE 1
#define CIRCLE_NEXT 2

class circle {
public:
    circle();
    // Add to another node
    circle(circle *& existing);
    virtual ~circle();
    // Distroy all in the list
    void destroy();
    // These need to be implimented by children of this base class
    virtual char match(circle *&) = 0;
    virtual char sort(circle *&) = 0;
    // Add a node this nodes list
    circle * add(circle *);
    // Find a node in the list
    circle * get(circle *&);
    // Remove a node from the list, get and delete
    char remove(circle *&);
private:
    circle * head;
    circle * next;
    circle * prev;
};
