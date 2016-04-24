/*
 * John Andersen
 * File: libtranposport test
*/

#include "transport.h"

int main() {
MACRO_TEST(test_car_unspecified);
MACRO_TEST(test_car_car_to_string);
MACRO_TEST(test_car_car_to_string_fail);
MACRO_TEST(test_car_car_from_string);
MACRO_TEST(test_car_car_from_string_fail);
MACRO_TEST(test_car_clear);
MACRO_TEST(test_trip_distance_in_miles);
MACRO_TEST(test_trip_distance_in_miles_fail);
MACRO_TEST(test_trip_trip_to_string);
MACRO_TEST(test_trip_trip_from_string);
MACRO_TEST(test_ride_ride_from_string);
return EXIT_SUCCESS;
}
