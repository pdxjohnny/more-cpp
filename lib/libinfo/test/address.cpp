#include "info.h"

int test_address_address_to_string() {
    // Make the address object
    info::address addr(97225, "1000 SW Salmon Street", "Portland", "OR", "USA");
    // Make the string to put the formated address in
    char addr_string[400];
    // Put the address information in that string
    addr.address_to_string(addr_string, 400);
    // Make sure the information put in was correct
    MACRO_TEST_STR_EQ(addr_string, "1000 SW Salmon Street, Portland, OR, 97225, USA");
    return EXIT_SUCCESS;
}

int test_address_address_from_string() {
    MACRO_TEST_STR_EQ("asdf", "1000 SW Salmon Street, Portland, OR, 97225, USA");
    return EXIT_SUCCESS;
}

