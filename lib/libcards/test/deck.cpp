#include "cards.h"

int test_cards_deck_correct_size() {
    cards::deck deck;
    MACRO_TEST_EQ(deck.size(), 52);
    return EXIT_SUCCESS;
}

int test_cards_deck_shuffle() {
    cards::deck deck;
    MACRO_TEST_EQ(deck.size(), 52);
    deck.shuffle();
    MACRO_TEST_EQ(deck.size(), 52);
    return EXIT_SUCCESS;
}
