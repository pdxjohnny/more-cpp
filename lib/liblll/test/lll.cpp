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
MACRO_TEST(test_lll_node_basic_get_index0);
MACRO_TEST(test_lll_node_basic_get);
MACRO_TEST(test_lll_basic_add);
MACRO_TEST(test_lll_basic_remove);
MACRO_TEST(test_lll_basic_remove_all);
MACRO_TEST(test_lll_basic_get);
MACRO_TEST(test_lll_basic_operator_subscript);
MACRO_TEST(test_lll_node_add);
MACRO_TEST(test_lll_node_remove_increasing);
MACRO_TEST(test_lll_node_remove_decreasing);
MACRO_TEST(test_lll_node_remove_all);
MACRO_TEST(test_lll_node_remove_self);
MACRO_TEST(test_lll_node_get_index0);
MACRO_TEST(test_lll_node_get);
MACRO_TEST(test_lll_node_correct_data);
MACRO_TEST(test_lll_add);
MACRO_TEST(test_lll_remove);
MACRO_TEST(test_lll_remove_all);
MACRO_TEST(test_lll_get);
MACRO_TEST(test_lll_operator_subscript);
MACRO_TEST(test_lll_correct_data);
return EXIT_SUCCESS;
}

