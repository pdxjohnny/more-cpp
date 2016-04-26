/*
 * John Andersen
 * File: libuser/include/libuser.h
*/
#include <iostream>

#ifndef LIBUSER
#define LIBUSER


// namespace user will hold different types of users. For example a stdin
// stdout basic user or a user connected over a socket
namespace user {
    class basic;
    class tcp;
};

// The user class can be extended to format the output before writing it to
// input_fd and output_fd by for example creating pipes and then pipeing output
// to them
class user::basic : public std::ostream, public std::streambuf {
    public:
        // A user with nothing defined assumes you want to take input from
        // stdin and output to stdout
        // user();
        basic();
        virtual ~basic();
        // Overflow is called when a carachter is sent to us
        virtual int overflow(int c);
};

#endif
