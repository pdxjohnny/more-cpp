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
return EXIT_SUCCESS;
}
