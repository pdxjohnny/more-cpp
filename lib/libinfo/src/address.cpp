#include "info.h"

info::address::address() : zip(0), street(NULL), city(NULL), state_or_province(NULL), country(NULL) {}

info::address::address(address & copy) : zip(copy.zip), street(NULL), city(NULL), state_or_province(NULL), country(NULL) {
    MACRO_STRCPY_IF_NOT_NULL(this->street, copy.street);
    MACRO_STRCPY_IF_NOT_NULL(this->city, copy.city);
    MACRO_STRCPY_IF_NOT_NULL(this->state_or_province, copy.state_or_province);
    MACRO_STRCPY_IF_NOT_NULL(this->country, copy.country);
}

info::address::address(int zip, const char * street, const char * city, const char * state_or_province, const char * country) : zip(zip), street(NULL), city(NULL), state_or_province(NULL), country(NULL) {
    MACRO_STRCPY_IF_NOT_NULL(this->street, street);
    MACRO_STRCPY_IF_NOT_NULL(this->city, city);
    MACRO_STRCPY_IF_NOT_NULL(this->state_or_province, state_or_province);
    MACRO_STRCPY_IF_NOT_NULL(this->country, country);
}

info::address::~address() {
    clear();
}

info::address & info::address::operator=(const info::address & copy) {
    this->zip = copy.zip;
    MACRO_STRCPY_IF_NOT_NULL(this->street, copy.street);
    MACRO_STRCPY_IF_NOT_NULL(this->city, copy.city);
    MACRO_STRCPY_IF_NOT_NULL(this->state_or_province, copy.state_or_province);
    MACRO_STRCPY_IF_NOT_NULL(this->country, copy.country);
    return *this;
}

void info::address::clear() {
    zip = 0;
    MACRO_DELETE_ARRAY_IF_NOT_NULL(street);
    MACRO_DELETE_ARRAY_IF_NOT_NULL(city);
    MACRO_DELETE_ARRAY_IF_NOT_NULL(state_or_province);
    MACRO_DELETE_ARRAY_IF_NOT_NULL(country);
}

int info::address::address_string_length() {
    // To store the length of the joined data
    int data_size = 0;
    // We also need to find out how many characters the zip will take up
    char * zip_buffer = NULL;
    if (zip != 0) {
        zip_buffer = new char[20];
        sprintf(zip_buffer, "%d", zip);
    }
    // Loop through all our data and add it find its size and then add it to
    // the buffer
    char ** data[] = {&street, &city, &state_or_province, &zip_buffer, &country, NULL};
    // Find the size of the joined data
    data_size = strings::join_length(data, INFO_ADDRESS_DELIM, INFO_ADDRESS_DONT_HAVE);
    // Get rid of the zip buffer
    delete[] zip_buffer;
    return data_size;
}

int info::address::address_to_string(char * buffer, int buffer_size) {
    // If join fails
    int err;
    // We also need to find out how many characters the zip will take up
    char * zip_buffer = NULL;
    if (zip != 0) {
        zip_buffer = new char[20];
        sprintf(zip_buffer, "%d", zip);
    }
    // Loop through all our data and add it find its size and then add it to
    // the buffer
    char ** data[] = {&street, &city, &state_or_province, &zip_buffer, &country, NULL};
    // Join the data together
    err = strings::join(buffer, data, INFO_ADDRESS_DELIM, INFO_ADDRESS_DONT_HAVE, buffer_size);
    // Get rid of the zip code as a string
    delete[] zip_buffer;
    // Success is determined by join
    return err;
}

int info::address::address_from_string(const char * from) {
    int err;
    // Lets pick a maximum value for the string to parse. Just so that we
    // ensure no one will pass us an insanly long string so that they can take
    // up memory
    if (strnlen(from, INFO_ADDRESS_MAX) >= INFO_ADDRESS_MAX) {
        return -1;
    }
    // Allocate a temporay zip buffer to scan that data in
    char * zip_buffer = NULL;
    // Parse them in
    // Loop through all our data and add it to the buffer
    char ** data[] = {&street, &city, &state_or_province, &zip_buffer,
        &country, NULL};
    err = strings::parse(data, from, INFO_ADDRESS_DELIM);
    // Parse may run out of data before it can fill all members so check to
    // make sure that the zip was filled before converting it
    if (zip_buffer == NULL) {
        return err;
    }
    // Convert the zip code from a string to an int
    zip = strtol(zip_buffer, NULL, 10);
    // No need for the zip code buffer anymore
    delete[] zip_buffer;
    // Check if zip code parsing failed
    if (errno == EINVAL || errno == ERANGE) {
        return -1;
    }
    // Success is determined by parse
    return err;
}

