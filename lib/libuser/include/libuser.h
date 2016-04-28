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
    class basic_stream;
    class obasic;
    class ibasic;
    class tcp;
};

// The user class can be extended to format the output before writing it to
// input_fd and output_fd by for example creating pipes and then pipeing output
// to them
class user::basic_stream : public std::streambuf
{
    public:
        virtual ~basic_stream();
        typedef typename traits_type::int_type int_type;
        typedef typename traits_type::off_type off_type;
        typedef typename traits_type::pos_type pos_type;
    protected:
        virtual int_type overflow (int_type c = traits_type::eof());
        virtual int_type underflow ();
};

class user::obasic : public std::iostream {
    public:
        obasic();
        virtual ~obasic();
    private:
        user::basic_stream obasic_stream_instance;
};

/*
class user::obasic : public std::ostream, public std::streambuf {
    public:
        // A user with nothing defined assumes you want to take input from
        // stdin and output to stdout
        // user();
        obasic();
        virtual ~obasic();
        // Overflow is called when a carachter is sent to us
        virtual int overflow(int c);
};
class user::ibasic : public std::istream, public std::streambuf {
    public:
        typedef typename traits_type::int_type int_type;
        // A user with nothing defined assumes you want to take input from
        // stdin and output to stdout
        // user();
        ibasic();
        virtual ~ibasic();
        // Overflow is called when a carachter is sent to us
        virtual int_type underflow();
};
*/
#endif
