/*
 * John Andersen
 * File: libuber/test/uber.cpp
*/

#include "uber.h"

int main() {
MACRO_TEST(test_uber_car_order);
MACRO_TEST(test_uber_car_unique_make_models);
MACRO_TEST(test_uber_car_save);
MACRO_TEST(test_uber_car_get);
MACRO_TEST(test_uber_car_get_not_found);
MACRO_TEST(test_uber_car_type_standard);
MACRO_TEST(test_uber_car_type_group);
MACRO_TEST(test_uber_car_type_premium);
MACRO_TEST(test_uber_ride_ride_from_string);
return EXIT_SUCCESS;
}
