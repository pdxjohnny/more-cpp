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

int test_cards_deck_random() {
    cards::deck deck;
    lll<cards::card> drawn;
    MACRO_TEST_EQ(deck.size(), 52);
    int i;
    int j;
    for (i = deck.size() - 1; i >= 0; --i) {
        drawn[i] = deck.random();
        for (j = drawn.size() - 1; j >= 0; --j) {
            if (i != j && drawn[j] == drawn[i] && drawn[i].same_suit(drawn[j])) {
                errno = -1;
                MACRO_LOG_FATAL("Two cards were the same%s", "");
            }
        }
    }
    MACRO_TEST_EQ(drawn.size(), 52);
    MACRO_TEST_EQ(deck.size(), 0);
    return EXIT_SUCCESS;
}
