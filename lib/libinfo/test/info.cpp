/*
 * John Andersen
 * File: libinfo/test/info.cpp
*/

#include "info.h"

int main() {
MACRO_TEST(test_address_unspecified);
MACRO_TEST(test_address_address_to_string);
MACRO_TEST(test_address_address_to_string_fail);
MACRO_TEST(test_address_address_from_string);
MACRO_TEST(test_address_address_from_string_fail);
MACRO_TEST(test_address_clear);
MACRO_TEST(test_location_lnglat);
MACRO_TEST(test_location_lnglat_clear_address);
MACRO_TEST(test_location_lnglat_clear_lnglat);
MACRO_TEST(test_location_distance_in_miles);
MACRO_TEST(test_location_distance_in_miles_fail);
MACRO_TEST(test_location_location_from_string);
return EXIT_SUCCESS;
}
