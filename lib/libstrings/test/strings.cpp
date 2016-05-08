/*
* John Andersen
* File: libtrings/test/strings.cpp
*/

#include "strings.h"

int main() {
MACRO_TEST(test_strings_readline);
MACRO_TEST(test_string_parse);
MACRO_TEST(test_string_parse_fail);
MACRO_TEST(test_string_join_length);
MACRO_TEST(test_string_join);
MACRO_TEST(test_string_join_fail);
MACRO_TEST(test_strings_string_constructor_null);
MACRO_TEST(test_strings_string_constructor_const_char);
MACRO_TEST(test_strings_string_constructor_string);
MACRO_TEST(test_strings_string_constructor_multiple_strings);
MACRO_TEST(test_strings_string_clr);
MACRO_TEST(test_strings_string_add_eq_const_char);
MACRO_TEST(test_strings_string_add_eq_string);
MACRO_TEST(test_strings_string_add_eq_const_char_string);
MACRO_TEST(test_strings_string_add_const_char);
MACRO_TEST(test_strings_string_add_string);
MACRO_TEST(test_strings_string_add_const_char_string);
MACRO_TEST(test_strings_string_compare_lessthan);
MACRO_TEST(test_strings_string_compare_lessthan_equal);
MACRO_TEST(test_strings_string_compare_greaterthan);
MACRO_TEST(test_strings_string_compare_greaterthan_equal);
MACRO_TEST(test_strings_string_compare_not_equal);
MACRO_TEST(test_strings_string_compare_equal);
return EXIT_SUCCESS;
}
