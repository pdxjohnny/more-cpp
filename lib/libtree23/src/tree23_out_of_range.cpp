#include <libtree23.h>

/*
 * Constructor
 */
tree23_out_of_range::tree23_out_of_range() {}

/*
 * Destructor
 */
tree23_out_of_range::~tree23_out_of_range() throw() {}

/*
 * Describes the error
 */
const char * tree23_out_of_range::what() const throw() {
    return "Could not retrive value at requested index";
}
