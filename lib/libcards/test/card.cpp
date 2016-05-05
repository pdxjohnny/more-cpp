#include "cards.h"

int test_cards_card_same_suit() {
    cards::card one('K', cards::SUIT_HEARTS);
    cards::card two('Q', cards::SUIT_HEARTS);
    MACRO_TEST_EQ(one.same_suit(two), true);
    return EXIT_SUCCESS;
}

/*
 * Test hearts
 */
int test_cards_card_same_color_hearts_hearts() {
    cards::card one('K', cards::SUIT_HEARTS);
    cards::card two('Q', cards::SUIT_HEARTS);
    MACRO_TEST_EQ(one.same_color(two), true);
    return EXIT_SUCCESS;
}

int test_cards_card_same_color_hearts_dimonds() {
    cards::card one('K', cards::SUIT_HEARTS);
    cards::card two('Q', cards::SUIT_DIMONDS);
    MACRO_TEST_EQ(one.same_color(two), true);
    return EXIT_SUCCESS;
}

int test_cards_card_same_color_hearts_spades() {
    cards::card one('K', cards::SUIT_HEARTS);
    cards::card two('Q', cards::SUIT_SPADES);
    MACRO_TEST_EQ(one.same_color(two), false);
    return EXIT_SUCCESS;
}

int test_cards_card_same_color_hearts_clubs() {
    cards::card one('K', cards::SUIT_HEARTS);
    cards::card two('Q', cards::SUIT_CLUBS);
    MACRO_TEST_EQ(one.same_color(two), false);
    return EXIT_SUCCESS;
}

/*
 * Tests dimonds
 */
int test_cards_card_same_color_dimonds_hearts() {
    cards::card one('K', cards::SUIT_DIMONDS);
    cards::card two('Q', cards::SUIT_HEARTS);
    MACRO_TEST_EQ(one.same_color(two), true);
    return EXIT_SUCCESS;
}

int test_cards_card_same_color_dimonds_dimonds() {
    cards::card one('K', cards::SUIT_DIMONDS);
    cards::card two('Q', cards::SUIT_DIMONDS);
    MACRO_TEST_EQ(one.same_color(two), true);
    return EXIT_SUCCESS;
}

int test_cards_card_same_color_dimonds_spades() {
    cards::card one('K', cards::SUIT_DIMONDS);
    cards::card two('Q', cards::SUIT_SPADES);
    MACRO_TEST_EQ(one.same_color(two), false);
    return EXIT_SUCCESS;
}

int test_cards_card_same_color_dimonds_clubs() {
    cards::card one('K', cards::SUIT_DIMONDS);
    cards::card two('Q', cards::SUIT_CLUBS);
    MACRO_TEST_EQ(one.same_color(two), false);
    return EXIT_SUCCESS;
}

/*
 * Tests spades
 */
int test_cards_card_same_color_spades_hearts() {
    cards::card one('K', cards::SUIT_SPADES);
    cards::card two('Q', cards::SUIT_HEARTS);
    MACRO_TEST_EQ(one.same_color(two), false);
    return EXIT_SUCCESS;
}

int test_cards_card_same_color_spades_dimonds() {
    cards::card one('K', cards::SUIT_SPADES);
    cards::card two('Q', cards::SUIT_DIMONDS);
    MACRO_TEST_EQ(one.same_color(two), false);
    return EXIT_SUCCESS;
}

int test_cards_card_same_color_spades_spades() {
    cards::card one('K', cards::SUIT_SPADES);
    cards::card two('Q', cards::SUIT_SPADES);
    MACRO_TEST_EQ(one.same_color(two), true);
    return EXIT_SUCCESS;
}

int test_cards_card_same_color_spades_clubs() {
    cards::card one('K', cards::SUIT_SPADES);
    cards::card two('Q', cards::SUIT_CLUBS);
    MACRO_TEST_EQ(one.same_color(two), true);
    return EXIT_SUCCESS;
}

/*
 * Test clubs
 */
int test_cards_card_same_color_clubs_hearts() {
    cards::card one('K', cards::SUIT_CLUBS);
    cards::card two('Q', cards::SUIT_HEARTS);
    MACRO_TEST_EQ(one.same_color(two), false);
    return EXIT_SUCCESS;
}

int test_cards_card_same_color_clubs_dimonds() {
    cards::card one('K', cards::SUIT_CLUBS);
    cards::card two('Q', cards::SUIT_DIMONDS);
    MACRO_TEST_EQ(one.same_color(two), false);
    return EXIT_SUCCESS;
}

int test_cards_card_same_color_clubs_spades() {
    cards::card one('K', cards::SUIT_CLUBS);
    cards::card two('Q', cards::SUIT_SPADES);
    MACRO_TEST_EQ(one.same_color(two), true);
    return EXIT_SUCCESS;
}

int test_cards_card_same_color_clubs_clubs() {
    cards::card one('K', cards::SUIT_CLUBS);
    cards::card two('Q', cards::SUIT_CLUBS);
    MACRO_TEST_EQ(one.same_color(two), true);
    return EXIT_SUCCESS;
}

/*
 * Test the equality operators for all cards
 */
int test_cards_card_equality() {
    return EXIT_SUCCESS;
}
