#include <cstdlib>
#include <cstring>
#include <stdint.h>
#include <cerrno>
#include <ctime>

#include <libmacro.h>
#include <libstrings.h>

#include <libuber.h>
int test_uber_car_order();
int test_uber_car_unique_make_models();
int test_uber_car_save();
int test_uber_car_get();
int test_uber_car_get_not_found();
int test_uber_car_type_standard();
int test_uber_car_type_group();
int test_uber_car_type_premium();
int test_uber_ride_ride_from_string();
