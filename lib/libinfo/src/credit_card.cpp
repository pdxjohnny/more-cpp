/*
 * John Andersen
 * File: libinfo/src/credit_card.cpp
*/

#include "info.h"

info::credit_card::credit_card() : number(0), exp_month(1), exp_year(0), cvc(0) {}

info::credit_card::credit_card(const info::credit_card & copy) : number(copy.number), exp_month(copy.exp_month), exp_year(copy.exp_year), cvc(copy.cvc) {}

info::credit_card::credit_card(long long int number, short exp_month, short exp_year, short cvc) : number(number), exp_month(exp_month), exp_year(exp_year), cvc(cvc) {}

info::credit_card::~credit_card() {}

info::credit_card & info::credit_card::operator=(const info::credit_card & copy) {
    this->number = copy.number;
    this->exp_month = copy.exp_month;
    this->exp_year = copy.exp_year;
    this->cvc = copy.cvc;
    return *this;
}

int info::credit_card::credit_card_to_string_readable(char * buffer, int buffer_length) {
    sprintf(buffer,
        "CC# %016lld, EXP Date %02d/%02d, CVC %03d",
        number, exp_month, exp_year, cvc
    );
    return EXIT_SUCCESS;
}

int info::credit_card::credit_card_to_string(char * buffer, int buffer_length) {
    // If join fails
    int err;
    // CC#
    char str_number[MACRO_NUM_TO_STR];
    sprintf(str_number, "%016lld", number);
    char * ptr_str_number = str_number;
    // EXP month
    char str_exp_month[MACRO_NUM_TO_STR];
    sprintf(str_exp_month, "%02d", exp_month);
    char * ptr_str_exp_month = str_exp_month;
    // EXP year
    char str_exp_year[MACRO_NUM_TO_STR];
    sprintf(str_exp_year, "%02d", exp_year);
    char * ptr_str_exp_year = str_exp_year;
    // CVC
    char str_cvc[MACRO_NUM_TO_STR];
    sprintf(str_cvc, "%03d", cvc);
    char * ptr_str_cvc = str_cvc;
    // The data we want to join
    char ** data[] = {&ptr_str_number, &ptr_str_exp_month, &ptr_str_exp_year, &ptr_str_cvc, NULL};
    // Join the data together
    err = strings::join(buffer, data, INFO_CREDIT_CARD_DELIM, INFO_CREDIT_CARD_DONT_HAVE, buffer_length);
    // Success is determined by join
    return err;
}

int info::credit_card::credit_card_from_string(const char * from) {
    int err;
    // Lets pick a maximum value for the string to parse. Just so that we
    // ensure no one will pass us an insanly long string so that they can take
    // up memory
    if (strnlen(from, INFO_CREDIT_CARD_MAX) >= INFO_CREDIT_CARD_MAX) {
        errno = E2BIG;
        return -1;
    }
    // Pointers that will hold parsed in strings
    char * str_number = NULL;
    char * str_exp_month = NULL;
    char * str_exp_year = NULL;
    char * str_cvc = NULL;
    // Parse them in
    char ** data[] = {&str_number, &str_exp_month, &str_exp_year, &str_cvc, NULL};
    // Loop through all our data and add it to the buffer
    err = strings::parse(data, from, INFO_CREDIT_CARD_DELIM);
    // Make sure parsing worked
    if (err != EXIT_SUCCESS) {
        MACRO_DELETE_ARRAY_IF_NOT_NULL(str_number);
        MACRO_DELETE_ARRAY_IF_NOT_NULL(str_exp_month);
        MACRO_DELETE_ARRAY_IF_NOT_NULL(str_exp_year);
        MACRO_DELETE_ARRAY_IF_NOT_NULL(str_cvc);
        return err;
    }
    // Check CC#
    errno = EXIT_SUCCESS;
    this->number = strtol(str_number, NULL, 10);
    // Check if parsing failed
    if (errno == ERANGE || errno == EINVAL) {
        err = -1;
        MACRO_DELETE_ARRAY_IF_NOT_NULL(str_number);
        MACRO_DELETE_ARRAY_IF_NOT_NULL(str_exp_month);
        MACRO_DELETE_ARRAY_IF_NOT_NULL(str_exp_year);
        MACRO_DELETE_ARRAY_IF_NOT_NULL(str_cvc);
        return err;
    }
    // Check EXP month
    errno = EXIT_SUCCESS;
    this->exp_month = strtol(str_exp_month, NULL, 10);
    // Check if parsing failed
    if (errno == ERANGE || errno == EINVAL) {
        err = -1;
        MACRO_DELETE_ARRAY_IF_NOT_NULL(str_number);
        MACRO_DELETE_ARRAY_IF_NOT_NULL(str_exp_month);
        MACRO_DELETE_ARRAY_IF_NOT_NULL(str_exp_year);
        MACRO_DELETE_ARRAY_IF_NOT_NULL(str_cvc);
        return err;
    }
    // Check EXP year
    errno = EXIT_SUCCESS;
    this->exp_year = strtol(str_exp_year, NULL, 10);
    // Check if parsing failed
    if (errno == ERANGE || errno == EINVAL) {
        err = -1;
        MACRO_DELETE_ARRAY_IF_NOT_NULL(str_number);
        MACRO_DELETE_ARRAY_IF_NOT_NULL(str_exp_month);
        MACRO_DELETE_ARRAY_IF_NOT_NULL(str_exp_year);
        MACRO_DELETE_ARRAY_IF_NOT_NULL(str_cvc);
        return err;
    }
    // Check CVC
    errno = EXIT_SUCCESS;
    this->cvc = strtol(str_cvc, NULL, 10);
    // Check if parsing failed
    if (errno == ERANGE || errno == EINVAL) {
        err = -1;
        MACRO_DELETE_ARRAY_IF_NOT_NULL(str_number);
        MACRO_DELETE_ARRAY_IF_NOT_NULL(str_exp_month);
        MACRO_DELETE_ARRAY_IF_NOT_NULL(str_exp_year);
        MACRO_DELETE_ARRAY_IF_NOT_NULL(str_cvc);
        return err;
    }
    MACRO_DELETE_ARRAY_IF_NOT_NULL(str_number);
    MACRO_DELETE_ARRAY_IF_NOT_NULL(str_exp_month);
    MACRO_DELETE_ARRAY_IF_NOT_NULL(str_exp_year);
    MACRO_DELETE_ARRAY_IF_NOT_NULL(str_cvc);
    // Success is determined by parse
    return err;
}
