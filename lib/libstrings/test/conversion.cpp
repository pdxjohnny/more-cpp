/*
 * John Andersen
 * File: libstrings/test/file.cpp
*/

#include "strings.h"


int test_strings_tobool() {
    char check[] = "true";
    bool res = strings::tobool(check);
    MACRO_TEST_EQ(res, true);
    return EXIT_SUCCESS;
}
