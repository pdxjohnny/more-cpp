/*
* John Andersen
* File: libcards/test/cards.cpp
*/

#include "cards.h"

int main() {
MACRO_TEST(test_cards_card_same_suit);
MACRO_TEST(test_cards_card_same_color_hearts_hearts);
MACRO_TEST(test_cards_card_same_color_hearts_dimonds);
MACRO_TEST(test_cards_card_same_color_hearts_spades);
MACRO_TEST(test_cards_card_same_color_hearts_clubs);
MACRO_TEST(test_cards_card_same_color_dimonds_hearts);
MACRO_TEST(test_cards_card_same_color_dimonds_dimonds);
MACRO_TEST(test_cards_card_same_color_dimonds_spades);
MACRO_TEST(test_cards_card_same_color_dimonds_clubs);
MACRO_TEST(test_cards_card_same_color_spades_hearts);
MACRO_TEST(test_cards_card_same_color_spades_dimonds);
MACRO_TEST(test_cards_card_same_color_spades_spades);
MACRO_TEST(test_cards_card_same_color_spades_clubs);
MACRO_TEST(test_cards_card_same_color_clubs_hearts);
MACRO_TEST(test_cards_card_same_color_clubs_dimonds);
MACRO_TEST(test_cards_card_same_color_clubs_spades);
MACRO_TEST(test_cards_card_same_color_clubs_clubs);
MACRO_TEST(test_cards_card_equality);
return EXIT_SUCCESS;
}
