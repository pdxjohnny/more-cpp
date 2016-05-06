#include <libdll.h>

/*
 * Constructor
 */
dll_out_of_range::dll_out_of_range() {}

/*
 * Destructor
 */
dll_out_of_range::~dll_out_of_range() throw() {}

/*
 * Describes the error
 */
const char * dll_out_of_range::what() const throw() {
    return "Could not retrive value at requested index";
}
