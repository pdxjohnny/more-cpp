/*
 * John Andersen
 * File: libstrings/include/libstrings.h
*/
#include <ostream>

#ifndef LIBSTRINGS
#define LIBSTRINGS

namespace strings {
    // Test functions sould return 42
    int test();
    // Given an array of string pointers this will move allong the src string
    // and place everything between the last string parsed and the delim into
    // the next string pointer. It returns -1 if it ran outo of data before it
    // could parse in all of the data requested. The array of string pointers
    // passed in should be NULL terminated. The strings will be allocated on
    // the heap so be sure to free them
    int parse(char *** dest, const char * src, const char * delim);
    // The reverse of parse_string this takes values and packs them into a
    // string. However this is passed a pointer to a string and needs to be
    // given a maximum value to avoid overflowing dest
    int join(char * dest, char *** src, const char * delim, const char * if_null, int dest_size);
    int join_length(char *** src, const char * delim, const char * if_null);
    // Read a file line by line and do_func with that line
    int readline(int fd, char * buffer, int buffer_size);
    // Conversion functions
    void toupper(char * buffer);
    bool tobool(const char * buffer);
    int toint(const char * buffer);
    // A string class
    class string;
    // Our operators to minipulate the string
    strings::string   operator +  (const strings::string &, const strings::string &);
    strings::string   operator +  (const strings::string &, const char *);
    strings::string   operator +  (const char *, const strings::string &);
    bool operator <  (const strings::string &, const strings::string &);
    bool operator <  (const strings::string &, const char *);
    bool operator <  (const char *, const strings::string &);
    bool operator <= (const strings::string &, const strings::string &);
    bool operator <= (const strings::string &, const char *);
    bool operator <= (const char *, const strings::string &);
    bool operator >  (const strings::string &, const strings::string &);
    bool operator >  (const strings::string &, const char *);
    bool operator >  (const char *, const strings::string &);
    bool operator >= (const strings::string &, const strings::string &);
    bool operator >= (const strings::string &, const char *);
    bool operator >= (const char *, const strings::string &);
    bool operator != (const strings::string &, const strings::string &);
    bool operator != (const strings::string &, const char *);
    bool operator != (const char *, const strings::string &);
    bool operator == (const strings::string &, const strings::string &);
    bool operator == (const strings::string &, const char *);
    bool operator == (const char *, const strings::string &);
    // Display the string
    std::ostream & operator << (std::ostream &, const string &);
};

class strings::string {
    public:
        // Constructors and destructors
        string();
        // Start with a string
        explicit string(const char *);
        string(const string &);
        // Join all the strings passed in
        explicit string(int num, ...);
        ~string();
        // Frees the string if it is non NULL
        void clr();
        // Returns the character array we hold
        const char * c_str() const;
        // Length of the string
        int length() const;
        // Access the internal string
        char & operator[](const int);
        // Set our internal string
        strings::string & operator = (const char);
        strings::string & operator = (const char *);
        strings::string & operator = (const strings::string &);
        // Our operators to minipulate the string
        strings::string & operator += (const strings::string &);
        strings::string & operator += (const char);
        strings::string & operator += (const char *);
        // Friends
        friend strings::string   operator +  (const strings::string &, const strings::string &);
        friend strings::string   operator +  (const strings::string &, const char *);
        friend strings::string   operator +  (const char *, const strings::string &);
        friend bool operator <  (const strings::string &, const strings::string &);
        friend bool operator <  (const strings::string &, const char *);
        friend bool operator <  (const char *, const strings::string &);
        friend bool operator <= (const strings::string &, const strings::string &);
        friend bool operator <= (const strings::string &, const char *);
        friend bool operator <= (const char *, const strings::string &);
        friend bool operator >  (const strings::string &, const strings::string &);
        friend bool operator >  (const strings::string &, const char *);
        friend bool operator >  (const char *, const strings::string &);
        friend bool operator >= (const strings::string &, const strings::string &);
        friend bool operator >= (const strings::string &, const char *);
        friend bool operator >= (const char *, const strings::string &);
        friend bool operator != (const strings::string &, const strings::string &);
        friend bool operator != (const strings::string &, const char *);
        friend bool operator != (const char *, const strings::string &);
        friend bool operator == (const strings::string &, const strings::string &);
        friend bool operator == (const strings::string &, const char *);
        friend bool operator == (const char *, const strings::string &);
        // Displays a string, up to that string to implement string::display
        // this is for showing the user the current strings
        friend std::ostream & operator << (std::ostream &, const strings::string &);
    private:
        // The string we are operating on
        char * data;
};

#endif
