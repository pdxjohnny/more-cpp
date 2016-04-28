/*
* John Andersen
* File: Test lll
*/

#include "lll.h"

int main () {
MACRO_TEST(test_lll_node_basic_add);
MACRO_TEST(test_lll_node_basic_remove_increasing);
MACRO_TEST(test_lll_node_basic_remove_decreasing);
MACRO_TEST(test_lll_node_basic_remove_all);
MACRO_TEST(test_lll_node_basic_remove_self);
return EXIT_SUCCESS;
}

