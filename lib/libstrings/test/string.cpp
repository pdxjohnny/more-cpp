#include "strings.h"

int test_strings_string_constructor_null() {
    strings::string str;
    MACRO_TEST_POINTER_EQ(str.c_str(), NULL);
    return EXIT_SUCCESS;
}

int test_strings_string_constructor_const_char() {
    strings::string str("test");
    MACRO_TEST_CANT_EQ(str.c_str(), NULL);
    MACRO_TEST_STR_EQ(str.c_str(), "test");
    return EXIT_SUCCESS;
}

int test_strings_string_constructor_string() {
    strings::string str("test");
    strings::string copy(str);
    MACRO_TEST_CANT_EQ(copy.c_str(), NULL);
    MACRO_TEST_STR_EQ(copy.c_str(), "test");
    return EXIT_SUCCESS;
}

int test_strings_string_constructor_multiple_strings() {
    strings::string str(3, "test", " some", " strings");
    MACRO_TEST_CANT_EQ(str.c_str(), NULL);
    MACRO_TEST_STR_EQ(str.c_str(), "test some strings");
    return EXIT_SUCCESS;
}

int test_strings_string_clr() {
    strings::string str(3, "test", " some", " strings");
    MACRO_TEST_CANT_EQ(str.c_str(), NULL);
    MACRO_TEST_STR_EQ(str.c_str(), "test some strings");
    str.clr();
    MACRO_TEST_POINTER_EQ(str.c_str(), NULL);
    return EXIT_SUCCESS;
}

int test_strings_string_add_eq_const_char() {
    strings::string str("test");
    str += " some strings";
    MACRO_TEST_CANT_EQ(str.c_str(), NULL);
    MACRO_TEST_STR_EQ(str.c_str(), "test some strings");
    return EXIT_SUCCESS;
}

int test_strings_string_add_eq_string() {
    strings::string str("test");
    str += strings::string(" some strings");
    MACRO_TEST_CANT_EQ(str.c_str(), NULL);
    MACRO_TEST_STR_EQ(str.c_str(), "test some strings");
    return EXIT_SUCCESS;
}

int test_strings_string_add_eq_const_char_string() {
    strings::string str("test");
    str += " some";
    str += strings::string(" strings");
    MACRO_TEST_CANT_EQ(str.c_str(), NULL);
    MACRO_TEST_STR_EQ(str.c_str(), "test some strings");
    return EXIT_SUCCESS;
}

int test_strings_string_add_const_char() {
    strings::string str("test");
    str = str + " some";
    str = str + " strings";
    MACRO_TEST_CANT_EQ(str.c_str(), NULL);
    MACRO_TEST_STR_EQ(str.c_str(), "test some strings");
    return EXIT_SUCCESS;
}

int test_strings_string_add_const_char_from_nothing() {
    strings::string str;
    str += "test";
    str += " some";
    str += " strings";
    MACRO_TEST_CANT_EQ(str.c_str(), NULL);
    MACRO_TEST_STR_EQ(str.c_str(), "test some strings");
    return EXIT_SUCCESS;
}

int test_strings_string_add_string() {
    strings::string str("test");
    str += " some" + strings::string(" strings");
    MACRO_TEST_CANT_EQ(str.c_str(), NULL);
    MACRO_TEST_STR_EQ(str.c_str(), "test some strings");
    return EXIT_SUCCESS;
}

int test_strings_string_add_const_char_string() {
    strings::string str("test");
    str += " some" + strings::string(" strings") + " more";
    MACRO_TEST_CANT_EQ(str.c_str(), NULL);
    MACRO_TEST_STR_EQ(str.c_str(), "test some strings more");
    return EXIT_SUCCESS;
}

int test_strings_string_compare_lessthan() {
    strings::string str("a");
    MACRO_TEST_EQ((str < "b"), true);
    return EXIT_SUCCESS;
}

int test_strings_string_compare_lessthan_equal() {
    strings::string str("a");
    MACRO_TEST_EQ((str <= "b"), true);
    MACRO_TEST_EQ((str <= "a"), true);
    return EXIT_SUCCESS;
}

int test_strings_string_compare_greaterthan() {
    strings::string str("b");
    MACRO_TEST_EQ((str > "a"), true);
    return EXIT_SUCCESS;
}

int test_strings_string_compare_greaterthan_equal() {
    strings::string str("b");
    MACRO_TEST_EQ((str > "a"), true);
    MACRO_TEST_EQ((str >= "b"), true);
    return EXIT_SUCCESS;
}

int test_strings_string_compare_not_equal() {
    strings::string str("a");
    MACRO_TEST_EQ((str != "b"), true);
    return EXIT_SUCCESS;
}

int test_strings_string_compare_equal() {
    strings::string str("a");
    MACRO_TEST_EQ((str == "a"), true);
    MACRO_TEST_EQ((str == "b"), false);
    return EXIT_SUCCESS;
}
