/*
 * John Andersen
 * File: liblll/test/lll_node_basic.cpp
*/
#include "lll.h"

#define lnb lll_node_basic

int test_lll_order() {
    lnb head;
    const int to_remove = 10;
    int i;
    for (i = 0; i < to_remove; ++i) {
        head.add();
    }
    MACRO_TEST_EQ(head.remove_all(), to_remove);
    return EXIT_SUCCESS;
}

