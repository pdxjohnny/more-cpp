/*
 * John Andersen
 * File: cards/src/cards.cpp
*/

#include "cards.h"


int main(int argc, char ** argv, char ** env) {
    // For catching errors
    // int err;
    if (argc < 1) {
        MACRO_LOG_FATAL("Usage: %s name_of_card_game", argv[0]);
    }
    char * game_name = argv[1];
    cards::game * game = cards::game_from_string(game_name);
    if (game == NULL) {
        MACRO_LOG_FATAL("Sorry we do not have the game \"%s\"", game_name);
    }
    // cards::play(game, player1, player2);
    return EXIT_SUCCESS;
}
