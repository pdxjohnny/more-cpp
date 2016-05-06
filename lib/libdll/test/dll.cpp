/*
* John Andersen
* File: Test dll
*/

#include "dll.h"

int main () {
MACRO_TEST(test_dll_node_basic_add);
MACRO_TEST(test_dll_node_basic_remove_increasing);
MACRO_TEST(test_dll_node_basic_remove_decreasing);
MACRO_TEST(test_dll_node_basic_remove_all);
MACRO_TEST(test_dll_node_basic_remove_self);
MACRO_TEST(test_dll_node_basic_get_index0);
MACRO_TEST(test_dll_node_basic_get);
MACRO_TEST(test_dll_node_basic_copy);
MACRO_TEST(test_dll_basic_add);
MACRO_TEST(test_dll_basic_remove);
MACRO_TEST(test_dll_basic_remove_all);
MACRO_TEST(test_dll_basic_get);
MACRO_TEST(test_dll_basic_operator_subscript);
MACRO_TEST(test_dll_basic_operator_copy);
MACRO_TEST(test_dll_node_add);
MACRO_TEST(test_dll_node_remove_increasing);
MACRO_TEST(test_dll_node_remove_decreasing);
MACRO_TEST(test_dll_node_remove_all);
MACRO_TEST(test_dll_node_remove_self);
MACRO_TEST(test_dll_node_get_index0);
MACRO_TEST(test_dll_node_get);
MACRO_TEST(test_dll_node_correct_data);
MACRO_TEST(test_dll_add);
MACRO_TEST(test_dll_remove);
MACRO_TEST(test_dll_remove_all);
MACRO_TEST(test_dll_get);
MACRO_TEST(test_dll_operator_subscript);
MACRO_TEST(test_dll_correct_data);
MACRO_TEST(test_dll_operator_copy);
return EXIT_SUCCESS;
}

