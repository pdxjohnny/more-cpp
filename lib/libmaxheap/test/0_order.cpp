/*
 * John Andersen
 * File: libmaxheap/test/0_order.cpp
*/

#include "maxheap.h"

int test_maxheap_order() {
    int i;
    char match[20];
    test_maxheap<char> b;
    for (i = 0; i < 20; ++i) {
        match[i] = (char)(i + 70);
        b[i] = (char)(i + 70);
    }
    match[20] = '\0';
    b[20] = '\0';

    char barr[20];
    char key[20];
    for (i = 0; i <= 20; ++i) {
        sprintf(key, "%020d", i);
        barr[i] = b[key];
    }
    MACRO_TEST_MEM_STR_EQ(barr, match);

    return EXIT_SUCCESS;
}

