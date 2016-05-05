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
 * Make sure the card throws and error when it is passed an invalid value
 */
int test_cards_card_invalid_card_value_error() {
    try {
        cards::card invalid('P', cards::SUIT_HEARTS);
    } catch (cards::invalid_card_value) {
        return EXIT_SUCCESS;
    }
    MACRO_PRINT_FILE_LINE("The card did not throw and inavlid_card_value exception when it was given and invalid value%s\n", "");
    return -1;
}

/*
 * Make sure the card throws and error when it is passed an invalid suit
 */
int test_cards_card_invalid_card_suit_error() {
    try {
        cards::card invalid('K', 'P');
    } catch (cards::invalid_card_suit) {
        return EXIT_SUCCESS;
    }
    MACRO_PRINT_FILE_LINE("The card did not throw and inavlid_card_suit exception when it was given and invalid suit%s\n", "");
    return -1;
}

/*
 * Test equality operator
 */
int test_cards_card_equality() {
    char value_one[] = {'K'};
    char value_two[] = {'K'};
    bool result[] = {1};
    const int to_check = sizeof(result);
    int i;
    for (i = 0; i < to_check; ++i) {
        cards::card one(value_one[i], cards::SUIT_CLUBS);
        cards::card two(value_two[i], cards::SUIT_CLUBS);
        MACRO_TEST_EQ(one == two, result[i]);
    }
    return EXIT_SUCCESS;
}

/*
 * Test lessthan operator
 */
int test_cards_card_lessthan() {
    char value_one[] = {'A', 'J', 'Q', '2', '3', '4', '5', '6', '7', '8', '9', '1'};
    char value_two[] = {'K', 'K', 'K', 'K', 'K', 'K', 'K', 'K', 'K', 'K', 'K', 'K'};
    const int to_check = sizeof(value_one);
    int i;
    for (i = 0; i < to_check; ++i) {
        cards::card one(value_one[i], cards::SUIT_CLUBS);
        cards::card two(value_two[i], cards::SUIT_CLUBS);
        if (!(one < two)) {
            MACRO_PRINT_FILE_LINE("%c should have been greater than %c\n", value_two[i], value_one[i]);
        }
        MACRO_TEST_EQ(one < two, true);
    }
    return EXIT_SUCCESS;
}
