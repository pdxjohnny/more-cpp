/*
 * John Andersen
 * File: libinfo/src/contact.cpp
*/

#include "info.h"

info::contact::contact() : name(NULL), phone(0) {}

info::contact::contact(const info::contact & copy) : name(NULL), phone(copy.phone) {
    MACRO_STRCPY_IF_NOT_NULL(this->name, copy.name);
}

info::contact::contact(const char * name, long long int phone) : name(NULL), phone(phone) {
    MACRO_STRCPY_IF_NOT_NULL(this->name, name);
}

info::contact::~contact() {
    MACRO_DELETE_ARRAY_IF_NOT_NULL(this->name);
}

info::contact & info::contact::operator=(const info::contact & copy) {
    this->phone = copy.phone;
    MACRO_STRCPY_IF_NOT_NULL(this->name, copy.name);
    return *this;
}

int info::contact::contact_to_string_readable(char * buffer, int buffer_length) {
    sprintf(buffer,
        "Name %s, Phone Number %010lld",
        name, phone
    );
    return EXIT_SUCCESS;
}

int info::contact::contact_to_string(char * buffer, int buffer_length) {
    // If join fails
    int err;
    // Phone
    char str_phone[MACRO_NUM_TO_STR];
    sprintf(str_phone, "%010lld", phone);
    char * ptr_str_phone = str_phone;
    // The data we want to join
    char ** data[] = {&name, &ptr_str_phone, NULL};
    // Join the data together
    err = strings::join(buffer, data, INFO_CONTACT_DELIM, INFO_CONTACT_DONT_HAVE, buffer_length);
    // Success is determined by join
    return err;
}

int info::contact::contact_from_string(const char * from) {
    int err;
    // Lets pick a maximum value for the string to parse. Just so that we
    // ensure no one will pass us an insanly long string so that they can take
    // up memory
    if (strnlen(from, INFO_CONTACT_MAX) >= INFO_CONTACT_MAX) {
        errno = E2BIG;
        return -1;
    }
    // Pointers that will hold parsed in strings
    char * str_phone = NULL;
    // Parse them in
    char ** data[] = {&name, &str_phone, NULL};
    // Loop through all our data and add it to the buffer
    err = strings::parse(data, from, INFO_CONTACT_DELIM);
    // Make sure parsing worked
    if (err != EXIT_SUCCESS) {
        MACRO_DELETE_ARRAY_IF_NOT_NULL(str_phone);
        return err;
    }
    // Check phone
    errno = EXIT_SUCCESS;
    this->phone = strtol(str_phone, NULL, 10);
    // Check if parsing failed
    if (errno == ERANGE || errno == EINVAL) {
        err = -1;
        MACRO_DELETE_ARRAY_IF_NOT_NULL(str_phone);
        return err;
    }
    MACRO_DELETE_ARRAY_IF_NOT_NULL(str_phone);
    // Success is determined by parse
    return err;
}
