#include <cstdlib>
#include <cstring>
#include <stdint.h>

#include <libmacro.h>
#include <libinfo.h>

int test_address_unspecified();
int test_address_address_to_string();
int test_address_address_to_string_fail();
int test_address_address_from_string();
int test_address_address_from_string_fail();
int test_address_clear();
int test_location_lnglat();
int test_location_lnglat_clear_address();
int test_location_lnglat_clear_lnglat();
int test_location_distance_in_miles();
int test_location_distance_in_miles_fail();
int test_location_location_from_string();
