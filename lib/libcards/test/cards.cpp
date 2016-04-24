/*
 * John Andersen
 * File: libcards/test/cards.cpp
*/

#include "cards.h"

int main() {
MACRO_TEST(test_cards_car_order);
MACRO_TEST(test_cards_car_unique_make_models);
MACRO_TEST(test_cards_car_save);
MACRO_TEST(test_cards_car_get);
MACRO_TEST(test_cards_car_get_not_found);
MACRO_TEST(test_cards_car_type_standard);
MACRO_TEST(test_cards_car_type_group);
MACRO_TEST(test_cards_car_type_premium);
MACRO_TEST(test_cards_ride_ride_from_string);
return EXIT_SUCCESS;
}
