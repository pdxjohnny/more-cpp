/*
 * John Andersen
 * File: cards/src/cards.cpp
*/

#include "cards.h"


int main(int argc, char ** argv, char ** env) {
    // The first agrument should be the name of the game we want to play
    char * game_name = NULL;
    if (argc < 1) {
        MACRO_LOG_FATAL("Usage: %s name_of_card_game", argv[0]);
    }
    game_name = argv[1];
    // Ask cards to provide us with an instance of that game
    cards::game * game = cards::game_from_string(game_name);
    if (game == NULL) {
        MACRO_LOG_FATAL("Sorry we do not have the game \"%s\"", game_name);
    }
    game->play(std::cin, std::cout);
    // We have no more use for the game
    MACRO_DELETE_IF_NOT_NULL(game);
    return EXIT_SUCCESS;
}
