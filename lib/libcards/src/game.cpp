#include <libcards.h>

/*
 * Initailize the game
 */
cards::game::game() {}

/*
 * Destroy the game
 */
cards::game::~game() {}

/*
 * Play the game. Accept the first player and add it to the list of players
 */
bool cards::game::play(cards::player & player_one) {
    players[players.size()] = player_one;
    return true;
}
