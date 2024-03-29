/*
 * John Andersen
 * File: libbst/test/0_order.cpp
*/

#include "bst.h"

int test_bst_order() {
    int i;
    char match[20];
    test_bst<char> b;
    for (i = 0; i < 20; ++i) {
        match[i] = (char)(i + 70);
        b[i] = (char)(i + 70);
    }
    match[19] = '\0';
    b[19] = '\0';

    char barr[19];
    for (i = 0; i < 20; ++i) {
        barr[i] = b[i];
    }
    MACRO_TEST_MEM_STR_EQ(barr, match);

    return EXIT_SUCCESS;
}

