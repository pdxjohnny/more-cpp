#include "info.h"

int main() {
MACRO_TEST(test_location_lnglat);
MACRO_TEST(test_address_unspecified);
MACRO_TEST(test_address_address_to_string);
MACRO_TEST(test_address_address_to_string_fail);
MACRO_TEST(test_address_address_from_string);
MACRO_TEST(test_address_address_from_string_fail);
MACRO_TEST(test_address_clear);
return EXIT_SUCCESS;
}
