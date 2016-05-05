#include <libcards.h>


/*
 * Initializes the hand. Some games the hand is a fixed size. If this
 * is the case specify the size, otherwise spcifiy 0 for a hand of
 * variable size. The size of the hand you can see that is. The cards
 * you cant see but are still in your posession are
 */
cards::hand::hand() {}

/*
 * Gets rid of the hand
 */
cards::hand::~hand() {}

/*
 * Draws a card from the deck and places it in the hand that is visable
 */
cards::card & cards::hand::draw_visable(cards::deck & source) {
    this->operator[](size()) = source.random();
    return this->operator[](size() - 1);
}

/*
 * Draws a card and places it in the not_visable cards we own
 */
cards::card & cards::hand::draw_not_visable(cards::deck & source) {
    not_visable[not_visable.size()] = source.random();
    return not_visable[not_visable.size() - 1];
}
