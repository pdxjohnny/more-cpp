/*
 * John Andersen
 * File: libstrings/test/strings.h
*/

#include <cstdlib>
#include <cstring>
#include <stdint.h>
#include <unistd.h>

#include <libmacro.h>
#include <libstrings.h>

int test_strings_tobool();
int test_strings_readline();
int test_string_parse();
int test_string_parse_fail();
int test_string_join_length();
int test_string_join();
int test_string_join_fail();
int test_strings_string_constructor_null();
int test_strings_string_constructor_const_char();
int test_strings_string_constructor_string();
int test_strings_string_constructor_multiple_strings();
int test_strings_string_clr();
int test_strings_string_add_eq_const_char();
int test_strings_string_add_eq_string();
int test_strings_string_add_eq_const_char_string();
int test_strings_string_add_const_char();
int test_strings_string_add_const_char_from_nothing();
int test_strings_string_add_string();
int test_strings_string_add_const_char_string();
int test_strings_string_compare_lessthan();
int test_strings_string_compare_lessthan_equal();
int test_strings_string_compare_greaterthan();
int test_strings_string_compare_greaterthan_equal();
int test_strings_string_compare_not_equal();
int test_strings_string_compare_equal();
