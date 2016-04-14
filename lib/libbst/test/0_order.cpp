#include "bst.h"

int test_bst_order() {
    int i;
    char match[20];
    test_bst<char> b;
    for (i = 0; i < 20; ++i) {
        match[i] = (char)(i + 70);
        b[i] = (char)(i + 70);
    }
    match[20] = '\0';
    b[20] = '\0';

    char barr[20];
    for (i = 0; i <= 20; ++i) {
        barr[i] = b[i];
    }
    MACRO_TEST_MEM_STR_EQ(barr, match);

    return EXIT_SUCCESS;
}

