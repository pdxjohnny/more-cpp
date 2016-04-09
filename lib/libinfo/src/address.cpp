#include "info.h"
#include <libinfo.h>

info::address::address() : zip(0), street(NULL), city(NULL), state_or_province(NULL), country(NULL) {}

info::address::address(int zip, const char * street, const char * city, const char * state_or_province, const char * country) : zip(zip), street(NULL), city(NULL), state_or_province(NULL), country(NULL) {
    MACRO_STRCPY_IF_NOT_NULL(this->street, street);
    MACRO_STRCPY_IF_NOT_NULL(this->city, city);
    MACRO_STRCPY_IF_NOT_NULL(this->state_or_province, state_or_province);
    MACRO_STRCPY_IF_NOT_NULL(this->country, country);
}

info::address::~address() {
    MACRO_DELETE_ARRAY_IF_NOT_NULL(street);
    MACRO_DELETE_ARRAY_IF_NOT_NULL(city);
    MACRO_DELETE_ARRAY_IF_NOT_NULL(state_or_province);
    MACRO_DELETE_ARRAY_IF_NOT_NULL(country);
}

int info::address::address_to_string(char * buffer, int buffer_size) {
    // Make sure that the buffer is big enough to fit our formated information
    // First we need to find out how long the data we have is
    int data_size = strlen(street) + strlen(city) + strlen(state_or_province) +
        strlen(country);
    // We also need to find out how many characters the zip will take up
    char * zip_buffer = new char[20];
    sprintf(zip_buffer, "%d", zip);
    data_size += strlen(zip_buffer);
    // Add 8 to the data_size to account for the four commas and spaces that
    // are added to deliminate fields
    data_size += 8;
    // Add one to the size of the data for the NULL terminator
    ++data_size;
    // If there is not enough room in the buffer then bail
    if (buffer_size < data_size) {
        delete[] zip_buffer;
        return -1;
    }
    // Loop through all our data and add it to the buffer
    char ** data_values[] = {&street, &city, &state_or_province, &zip_buffer, &country, NULL};
    char *** data = data_values;
    // If we dont have data on something report n/a
    char dont_have[] = "n/a";
    // The string to add to the buffer
    char * add;
    for (; *data != NULL; data++) {
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

