/*
 * John Andersen
 * File: libinfo/src/customer.cpp
*/

#include "info.h"

info::customer::customer() {}

info::customer::customer(const info::customer & copy) : info::contact(copy), info::credit_card(copy) {}

info::customer::customer(info::contact & contact, info::credit_card & credit_card) : info::contact(contact), info::credit_card(credit_card) {}

info::customer::~customer() {}

info::customer & info::customer::operator=(const info::customer & copy) {
    info::contact::operator=(copy);
    info::credit_card::operator=(copy);
    return *this;
}

int info::customer::customer_to_string_readable(char * buffer, int buffer_length) {
    // Contact
    char str_contact[INFO_CONTACT_MAX];
    contact_to_string_readable(str_contact, INFO_CONTACT_MAX);
    // Credit Card
    char str_credit_card[INFO_CREDIT_CARD_MAX];
    credit_card_to_string_readable(str_credit_card, INFO_CREDIT_CARD_MAX);
    // Format it
    sprintf(buffer,
        "%s\n%s",
        str_contact,
        str_credit_card
    );
    return EXIT_SUCCESS;
}

int info::customer::customer_to_string(char * buffer, int buffer_length) {
    // If join fails
    int err;
    // Contact
    char str_contact[INFO_CONTACT_MAX];
    contact_to_string(str_contact, INFO_CONTACT_MAX);
    char * ptr_str_contact = str_contact;
    // Credit Card
    char str_credit_card[INFO_CREDIT_CARD_MAX];
    credit_card_to_string(str_credit_card, INFO_CREDIT_CARD_MAX);
    char * ptr_str_credit_card = str_credit_card;
    // The data we want to join
    char ** data[] = {&ptr_str_contact, &ptr_str_credit_card, NULL};
    // Join the data together
    err = strings::join(buffer, data, INFO_CUSTOMER_DELIM, INFO_CUSTOMER_DONT_HAVE, buffer_length);
    // Success is determined by join
    return err;
}

int info::customer::customer_from_string(const char * from) {
    int err;
    // Lets pick a maximum value for the string to parse. Just so that we
    // ensure no one will pass us an insanly long string so that they can take
    // up memory
    if (strnlen(from, INFO_CUSTOMER_MAX) >= INFO_CUSTOMER_MAX) {
        errno = E2BIG;
        return -1;
    }
    // Pointers that will hold parsed in strings
    char * str_contact = NULL;
    char * str_credit_card = NULL;
    // Parse them in
    char ** data[] = {&str_contact, &str_credit_card, NULL};
    // Loop through all our data and add it to the buffer
    err = strings::parse(data, from, INFO_CUSTOMER_DELIM);
    // Make sure parsing worked
    if (err != EXIT_SUCCESS) {
        MACRO_DELETE_ARRAY_IF_NOT_NULL(str_contact);
        MACRO_DELETE_ARRAY_IF_NOT_NULL(str_credit_card);
        return err;
    }
    // Check contact
    err = contact_from_string(str_contact);
    if (err != EXIT_SUCCESS) {
        MACRO_DELETE_ARRAY_IF_NOT_NULL(str_contact);
        MACRO_DELETE_ARRAY_IF_NOT_NULL(str_credit_card);
        return err;
    }
    // Check credit_card
    err = credit_card_from_string(str_credit_card);
    if (err != EXIT_SUCCESS) {
        MACRO_DELETE_ARRAY_IF_NOT_NULL(str_contact);
        MACRO_DELETE_ARRAY_IF_NOT_NULL(str_credit_card);
        return err;
    }
    MACRO_DELETE_ARRAY_IF_NOT_NULL(str_contact);
    MACRO_DELETE_ARRAY_IF_NOT_NULL(str_credit_card);
    // Success is determined by parse
    return err;
}
