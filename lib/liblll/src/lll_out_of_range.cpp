#include <liblll.h>

/*
 * Constructor
 */
lll_out_of_range::lll_out_of_range() {}

/*
 * Destructor
 */
lll_out_of_range::~lll_out_of_range() throw() {}

/*
 * Describes the error
 */
const char * lll_out_of_range::what() const throw() {
    return "Could not retrive value at requested index";
}
