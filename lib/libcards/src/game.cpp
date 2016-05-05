#include "cards.h"

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

/*
 * Displays self to all of the players
 */
void cards::game::display_all() {
    int i;
    for (i = players.size() - 1; i >= 0; --i) {
        operator<<(players[i]->out(), *this);
    }
}

/*
 * Displays the game. This should be overridden or else it wont display
 * anything
 */
void cards::game::display(std::ostream & out) {}

/*
 * Displays a game, up to that game to implement game::display
 * this is for showing the user the current cards
 */
std::ostream & cards::operator<<(std::ostream & out, cards::game & game) {
    game.display(out);
    return out;
}
