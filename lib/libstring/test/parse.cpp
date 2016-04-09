#include "string.h"

int test_string_parse_string() {
    char * one = NULL;
    char * two = NULL;
    char * three = NULL;
    char ** data[] = {&one, &two, &three, NULL};
    string::parse(data, "frist, second, third", ", ");
    MACRO_TEST_STR_EQ(one, "frist");
    MACRO_TEST_STR_EQ(two, "second");
    MACRO_TEST_STR_EQ(three, "third");
    MACRO_DELETE_ARRAY_IF_NOT_NULL(one);
    MACRO_DELETE_ARRAY_IF_NOT_NULL(two);
    MACRO_DELETE_ARRAY_IF_NOT_NULL(three);
    return EXIT_SUCCESS;
}

