#include "strings.h"

int main() {
MACRO_TEST(test_string_parse);
MACRO_TEST(test_string_parse_fail);
MACRO_TEST(test_string_join_length);
MACRO_TEST(test_string_join);
MACRO_TEST(test_string_join_fail);
return EXIT_SUCCESS;
}
