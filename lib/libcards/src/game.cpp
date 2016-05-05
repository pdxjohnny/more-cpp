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

/*
 * Pass next turn the current player
 */
bool cards::game::next_turn() {
    bool keep_going = turn(players[current_player]);
    ++current_player;
    if (current_player >= players.size()) {
        current_player = 0;
    }
    MACRO_LOG_STR("Next player is");
    MACRO_LOG_INT(current_player);
    return keep_going;
}
