#include <liberrors.h>

/*
 * Constructor
 */
index_out_of_range::index_out_of_range() {}

/*
 * Destructor
 */
index_out_of_range::~index_out_of_range() throw() {}

/*
 * Describes the error
 */
const char * index_out_of_range::what() const throw() {
    return "Could not retrive value at requested index";
}
