/*
 * John Andersen
 * File: liberrors/include/liberrors.h
*/
#include <exception>

/*
 * This exception is thrown if an index could not be accessed
 */
class index_out_of_range : public std::exception {
    public:
        index_out_of_range();
        ~index_out_of_range() throw();
        virtual const char * what() const throw();
};

