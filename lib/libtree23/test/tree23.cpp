/*
* John Andersen
* File: Test tree23
*/

#include "tree23.h"

int main () {
MACRO_TEST(test_tree23_node_basic_add);
MACRO_TEST(test_tree23_node_basic_remove_increasing);
MACRO_TEST(test_tree23_node_basic_remove_decreasing);
MACRO_TEST(test_tree23_node_basic_remove_all);
MACRO_TEST(test_tree23_node_basic_remove_self);
MACRO_TEST(test_tree23_node_basic_get_index0);
MACRO_TEST(test_tree23_node_basic_get);
MACRO_TEST(test_tree23_node_basic_copy);
MACRO_TEST(test_tree23_basic_add);
MACRO_TEST(test_tree23_basic_remove);
MACRO_TEST(test_tree23_basic_remove_all);
MACRO_TEST(test_tree23_basic_get);
MACRO_TEST(test_tree23_basic_operator_subscript);
MACRO_TEST(test_tree23_basic_operator_copy);
MACRO_TEST(test_tree23_node_add);
MACRO_TEST(test_tree23_node_remove_increasing);
MACRO_TEST(test_tree23_node_remove_decreasing);
MACRO_TEST(test_tree23_node_remove_all);
MACRO_TEST(test_tree23_node_remove_self);
MACRO_TEST(test_tree23_node_get_index0);
MACRO_TEST(test_tree23_node_get);
MACRO_TEST(test_tree23_node_correct_data);
MACRO_TEST(test_tree23_add);
MACRO_TEST(test_tree23_remove);
MACRO_TEST(test_tree23_remove_all);
MACRO_TEST(test_tree23_get);
MACRO_TEST(test_tree23_operator_subscript);
MACRO_TEST(test_tree23_correct_data);
MACRO_TEST(test_tree23_operator_copy);
return EXIT_SUCCESS;
}

