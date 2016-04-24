/*
 * John Andersen
 * File: libinfo/test/address.cpp
*/

#include "info.h"

int test_address_unspecified() {
    // Make the address object
    info::address addr;
    // Make the string to put the formated address in
    char addr_string[400];
    // Put the address information in that string
    MACRO_TEST_EQ(addr.address_to_string(addr_string, 400), 0);
    // Make sure the information put in was correct
    MACRO_TEST_STR_EQ(addr_string, "n/a, n/a, n/a, n/a, n/a");
    return EXIT_SUCCESS;
}

int test_address_address_to_string() {
    // Make the address object
    info::address addr(97225, "1000 SW Salmon Street", "Portland", "OR", "USA");
    // Make the string to put the formated address in
    char addr_string[400];
    // Put the address information in that string
    MACRO_TEST_EQ(addr.address_to_string(addr_string, 400), 0);
    // Make sure the information put in was correct
    MACRO_TEST_STR_EQ(addr_string, "1000 SW Salmon Street, Portland, OR, 97225, USA");
    return EXIT_SUCCESS;
}

int test_address_address_to_string_fail() {
    // Make the address object
    info::address addr(97225, "1000 SW Salmon Street", "Portland", "OR", "USA");
    // Make the string to put the formated address in
    char addr_string[3];
    // Cant put all that in tree characters! Should be -1 for fail
    MACRO_TEST_EQ(addr.address_to_string(addr_string, 3), -1);
    return EXIT_SUCCESS;
}

int test_address_address_from_string() {
    // Make the address object
    info::address addr;
    // Fill the address with this information
    MACRO_TEST_EQ(addr.address_from_string("1000 SW Salmon Street, Portland, OR, 97225, USA"), 0);
    // Make the string to put the formated address in
    char addr_string[400];
    // Put the address information in that string
    MACRO_TEST_EQ(addr.address_to_string(addr_string, 400), 0);
    // Make sure the information put in was correct
    MACRO_TEST_STR_EQ(addr_string, "1000 SW Salmon Street, Portland, OR, 97225, USA");
    return EXIT_SUCCESS;
}

int test_address_address_from_string_fail() {
    // Make the address object
    info::address addr;
    // A really long address
    char long_address[600];
    // Because valgrind doesnt like memset
    int i;
    for (i = 0; i < 600; ++i) {
        long_address[i] = 'a';
    }
    long_address[600] = '\0';
    // Fill the address with the information that is too long
    MACRO_TEST_EQ(addr.address_from_string(long_address), -1);
    return EXIT_SUCCESS;
}

int test_address_clear() {
    // Make the address object
    info::address addr(97225, "1000 SW Salmon Street", "Portland", "OR", "USA");
    // Make the string to put the formated address in
    char addr_string[400];
    // Put the address information in that string
    MACRO_TEST_EQ(addr.address_to_string(addr_string, 400), 0);
    // Make sure the information put in was correct
    MACRO_TEST_STR_EQ(addr_string, "1000 SW Salmon Street, Portland, OR, 97225, USA");
    // It is set so clear it
    addr.clear();
    // Put the address information in that string
    MACRO_TEST_EQ(addr.address_to_string(addr_string, 400), 0);
    // Make sure the information put in was correct
    MACRO_TEST_STR_EQ(addr_string, "n/a, n/a, n/a, n/a, n/a");
    return EXIT_SUCCESS;
}

