#include <libcards.h>

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
bool cards::solitare::turn(player & current_player) {
    return true;
}
