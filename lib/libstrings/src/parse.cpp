#include "strings.h"

int strings::join_length(char *** src, const char * delim, const char * if_null) {
    // Make sure that the buffer is big enough to fit our formated information
    // First we need to find out how long the data we have is
    int data_size = 0;
    // If we dont have data on something report whatever was selected for
    // if_null
    int if_null_length = 0;
    if (if_null != NULL) {
        if_null_length = strlen(if_null);
    }
    // The length of the delim
    int delim_length = strlen(delim);
    // Loop through all our data and add it find its size and then add it to
    // the buffer
    for (; *src != NULL; ++src) {
        // If there is a string to copy then add the length of the string
        if (**src != NULL) {
            data_size += strlen(**src);
        // Otherwize add the length of the if_null sting which will be added
        } else {
            data_size += if_null_length;
        }
        // If the next one is not the last one then there will be a comamnd and
        // a space after it so add two to the size
        if (src[1] != NULL) {
            data_size += delim_length;
        }
    }
    // Add one to the size of the data for the NULL terminator
    ++data_size;
    return data_size;
}

int strings::join(char * dest, char *** src, const char * delim, const char * if_null, int dest_size) {
    // If we dont have data on something report whatever was selected for
    // if_null
    int delim_length = strlen(delim);
    // If there is not enough room in the buffer then we need to know when to
    // bail
    int dest_length = 0;
    // The number of bytes we have copyied into dest
    uintptr_t add_and_delim_length = 0;
    // The string to add to the buffer
    char * add;
    for (; *src != NULL; ++src) {
        // We wont be modifying add so this is ok
        add = (char *)if_null;
        // If we have the data then append it
        if (**src != NULL) {
            add = **src;
        }
        // If this is not the last element to add to the buffer then put a
        // comma and a space
        // src[0] is the string we are on and src[1] is the next possible
        if (src[1] != NULL) {
            add_and_delim_length = (uintptr_t)(strlen(add) + delim_length);
            dest_length += add_and_delim_length;
            // If the dest_length is larger than the dest_size then this will
            // cause an overflow and we should exit with a failure
            if (dest_size <= dest_length) {
                return -1;
            }
            // Copy the string to add and the delim into the destination string
            sprintf(dest, "%s%s", add, delim);
            // Move us forward to the next location to add at
            dest += add_and_delim_length;
        // If there is not another then this is the last itteration of the loop
        // and thou shalt not add a comma
        } else {
            add_and_delim_length = (uintptr_t)strlen(add);
            dest_length += add_and_delim_length;
            // If the dest_length is larger than the dest_size then this will
            // cause an overflow and we should exit with a failure
            if (dest_size <= dest_length) {
                return -1;
            }
            sprintf(dest, "%s", add);
            // Move us forward to the next location to add at
            dest += add_and_delim_length;
        }
    }
    // Yay we made it
    return EXIT_SUCCESS;
}

int strings::parse(char *** dest, const char * from, const char * delim) {
    // The a pointer to the end of the data we are looking for
    const char * data_end;
    uintptr_t data_length;
    uintptr_t delim_length = strlen(delim);
    for (; *dest != NULL; ++dest) {
        data_length = 0;
        // Look for the delim
        data_end = strstr(from, delim);
        // If we cant find it then the current element of dest is the last one
        // we are able to store data in
        if (data_end == NULL) {
            // We want to avoid the negavtive number from NULL - from so just
            // copy and exit
            MACRO_STRCPY_IF_NOT_NULL(**dest, from);
            // If the next element to parsee data into is not NULL then we are
            // expecting to get more data but because we have no more data we
            // should return an error
            if (dest[1] != NULL) {
                return -1;
            }
            break;
        }
        data_length = data_end - from;
        // Copy but add 1 to the length of the NULL terminator
        MACRO_STRNCPY_IF_NOT_NULL(**dest, from, data_length + 1);
        (**dest)[data_length] = '\0';
        // We just parsed in a string so move on to where the next one whould
        // start
        from += (uintptr_t)(data_length + delim_length);
    }
    // Holla we win
    return EXIT_SUCCESS;
}

