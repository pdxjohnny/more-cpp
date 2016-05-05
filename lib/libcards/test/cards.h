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

#include <libcards.h>
int test_cards_card_same_suit();
int test_cards_card_same_color_hearts_hearts();
int test_cards_card_same_color_hearts_dimonds();
int test_cards_card_same_color_hearts_spades();
int test_cards_card_same_color_hearts_clubs();
int test_cards_card_same_color_dimonds_hearts();
int test_cards_card_same_color_dimonds_dimonds();
int test_cards_card_same_color_dimonds_spades();
int test_cards_card_same_color_dimonds_clubs();
int test_cards_card_same_color_spades_hearts();
int test_cards_card_same_color_spades_dimonds();
int test_cards_card_same_color_spades_spades();
int test_cards_card_same_color_spades_clubs();
int test_cards_card_same_color_clubs_hearts();
int test_cards_card_same_color_clubs_dimonds();
int test_cards_card_same_color_clubs_spades();
int test_cards_card_same_color_clubs_clubs();
int test_cards_card_invalid_card_value_error();
int test_cards_card_invalid_card_suit_error();
int test_cards_card_equality();
