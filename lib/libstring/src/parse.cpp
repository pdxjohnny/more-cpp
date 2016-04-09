#include "string.h"
#include <libstring.h>
/*
int string::address_string_length() {
    // Make sure that the buffer is big enough to fit our formated information
    // First we need to find out how long the data we have is
    int data_size = 0;
    // If we dont have data on something report n/a
    char dont_have[] = INFO_ADDRESS_DONT_HAVE;
    int dont_have_length = strlen(dont_have);
    // We also need to find out how many characters the zip will take up
    char * zip_buffer = NULL;
    if (zip != 0) {
        zip_buffer = new char[20];
        sprintf(zip_buffer, "%d", zip);
    }
    // Loop through all our data and add it find its size and then add it to
    // the buffer
    char ** data_values[] = {&street, &city, &state_or_province, &zip_buffer, &country, NULL};
    // Pointer for looping through the data_valus array
    char *** data;
    for (data = data_values; *data != NULL; ++data) {
        // If there is a string to copy then add the length of the string
        if (**data != NULL) {
            data_size += strlen(**data);
        // Otherwize add the length of the dont_have sting which will be added
        } else {
            data_size += dont_have_length;
        }
        // If the next one is not the last one then there will be a comamnd and
        // a space after it so add two to the size
        if (data[1] != NULL) {
            data_size += 2;
        }
    }
    // Add one to the size of the data for the NULL terminator
    ++data_size;
    //  Get rid of the zip buffer
    delete[] zip_buffer;
    return data_size;
}

int string::address_to_string(char * buffer, int buffer_size) {
    // If we dont have data on something report n/a
    char dont_have[] = INFO_ADDRESS_DONT_HAVE;
    // We also need to find out how many characters the zip will take up
    char * zip_buffer = NULL;
    if (zip != 0) {
        zip_buffer = new char[20];
        sprintf(zip_buffer, "%d", zip);
    }
    // Loop through all our data and add it find its size and then add it to
    // the buffer
    char ** data_values[] = {&street, &city, &state_or_province, &zip_buffer, &country, NULL};
    // Pointer for looping through the data_valus array
    char *** data;
    // If there is not enough room in the buffer then bail
    if (buffer_size < address_string_length()) {
        delete[] zip_buffer;
        return -1;
    }
    // The string to add to the buffer
    char * add;
    for (data = data_values; *data != NULL; ++data) {
        add = dont_have;
        // If we have the data then append that we have it
        if (**data != NULL) {
            add = **data;
        }
        // If this is not the last element to add to the buffer then put a
        // comma and a space
        // data[0] is the string we are on and data[1] is the next possible
        if (data[1] != NULL) {
            sprintf(buffer, "%s, ", add);
            buffer += (uintptr_t)(strlen(add) + 2);
        // If there is not another then this is the last itteration of the loop
        // and thou shalt not add a comma
        } else {
            sprintf(buffer, "%s", add);
        }
    }
    // Get rid of the zip code as a string
    delete[] zip_buffer;
    // Yay we made it
    return EXIT_SUCCESS;
}
*/
int string::parse(char *** dest, const char * from, const char * delim) {
    // The a pointer to the end of the data we are looking for
    const char * data_end;
    uintptr_t data_length;
    uintptr_t delim_length = strlen(delim);
    for (; *dest != NULL; ++dest) {
        data_length = 0;
        // Look for the delim
        data_end = strstr(from, delim);
        // If we cant find it and there are elements left to store data in we
        // know that we will not be able to fill them all so there was an error
        if (data_end == NULL && dest[1] != NULL) {
            return -1;
        } else if (data_end == NULL) {
            // We want to avoid the negavtive number from NULL - from so just
            // copy and exit
            MACRO_STRCPY_IF_NOT_NULL(**dest, from);
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

