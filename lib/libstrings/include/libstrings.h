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
};

#endif

