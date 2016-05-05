#include <libcards.h>

/*
 * Initailize the game
 */
cards::game::game() : current_player(0) {}

/*
 * Destroy the game
 */
cards::game::~game() {}

/*
 * Play the game. Accept the first player and add it to the list of players
 */
bool cards::game::play(int num_players, ...) {
    va_list args;
    va_start(args, num_players);
    int players_added = 0;
    // Add all the players to our list of players
    for (players_added = num_players; players_added > 0; --players_added) {
        players[players.size()] = va_arg(args, cards::player *);
    }
    va_end(args);
    return true;
}

/*
 * Pass next turn the current player
 */
bool cards::game::next_turn() {
    if (current_player >= players.size()) {
        current_player = 0;
    }
    bool keep_going = turn(*(players[current_player]));
    ++current_player;
    return keep_going;
}
