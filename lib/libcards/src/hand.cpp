#include "cards.h"


/*
 * Initializes the hand. Some games the hand is a fixed size. If this
 * is the case specify the size, otherwise spcifiy 0 for a hand of
 * variable size. The size of the hand you can see that is. The cards
 * you cant see but are still in your posession are
 */
cards::hand::hand() : num_visable(1) {}

/*
 * Gets rid of the hand
 */
cards::hand::~hand() {}

/*
 * Draws a card from the deck and places it in the hand that is visable
 */
cards::card & cards::hand::draw_visable(cards::deck & source) {
    if (size() + 1 > num_visable) {
        return draw_not_visable(source);
    }
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

/*
 * Sets the number of cards that are visable to us
 */
void cards::hand::set_num_visable(int num) {
    num_visable = num;
}

/*
 * When a card is removed from our visable set we need to add one of our cards
 * from not visable if we can to maintian the right num_visable
 */
bool cards::hand::remove(int index) {
    lll<cards::card>::remove(index);
    if (size() < num_visable && not_visable.size() > 0) {
        this->operator[](size()) = not_visable[not_visable.size() - 1];
        not_visable.remove(not_visable.size() - 1);
    }
    return true;
}

/*
 * Displays the hand
 */
void cards::hand::display(std::ostream & out) {
    int hand_size = size();
    int i;
    for (i = 0; i < hand_size; ++i) {
        out << this->operator[](i);
        if (i != 0 && (i + 1) % 5 == 0) {
            out << std::endl;
        } else {
            out << "  ";
        }
    }
}

/*
 * This is for showing the user the current cards
 */
std::ostream & cards::operator<<(std::ostream & out, cards::hand & hand) {
    hand.display(out);
    return out;
}
