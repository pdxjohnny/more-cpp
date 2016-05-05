#include "cards.h"

/*
 * Create the game
 */
cards::solitare::solitare() {}

/*
 * Clean up the game when its over
 */
cards::solitare::~solitare() {}

/*
 * Turn asks the player what we should do on this turn
 */
bool cards::solitare::turn(cards::player & curr) {
    curr.out() << *this;
    return true;
}

/*
 * Displays the board
 */
void cards::solitare::display(std::ostream & out) {
    return;
}
