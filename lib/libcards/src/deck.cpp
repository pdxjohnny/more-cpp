#include <libcards.h>

/*
 * Initailizes the deck
 */
cards::deck::deck() {
    // So that random works
    std::srand(0U);
    shuffle();
}

/*
 * Gets rid of the deck
 */
cards::deck::~deck() {}

/*
 * Lets you access a random card from the deck. That card will not be
 * available to access again until you have shuffled the deck. If there
 * are no more cards to be played random throws a no more cards
 * exception. We return by value because the card will be removed from
 * the deck and if we were to return by refernece the card would be no
 * longer available
 */
cards::card cards::deck::random() {
    int index = std::rand() % (size() - 1);
    cards::card tmp = this->operator[](index);
    remove(index);
    return tmp;
}

/*
 * Shuffling the deck makes it so all the cards can be accessed by
 * random again
 */
void cards::deck::shuffle() {
    char suits[] = {
        cards::SUIT_HEARTS,
        cards::SUIT_DIMONDS,
        cards::SUIT_SPADES,
        cards::SUIT_CLUBS,
    };
    char values[] = {
        'A', '2', '3', '4', '5', '6', '7', '8', '9', '1', 'J', 'Q', 'K'
    };
    this->remove_all();
    int i = 0;
    int j = 0;
    int k = 0;
    for (i = sizeof(suits) - 1; i >= 0; --i) {
        for (j = sizeof(values) - 1; j >= 0; --j) {
            cards::card insert_card(values[j], suits[i]);
            this->operator[](k) = insert_card;
            ++k;
        }
    }
}
