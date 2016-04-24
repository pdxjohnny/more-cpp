/*
 * John Andersen
 * File: libcards/test/cards.h
*/

#include <cstdlib>
#include <cstring>
#include <stdint.h>
#include <cerrno>
#include <ctime>

#include <libmacro.h>
#include <libstrings.h>

#include <libcards.h>
int test_cards_car_order();
int test_cards_car_unique_make_models();
int test_cards_car_save();
int test_cards_car_get();
int test_cards_car_get_not_found();
int test_cards_car_type_standard();
int test_cards_car_type_group();
int test_cards_car_type_premium();
int test_cards_ride_ride_from_string();
