/*
 * John Andersen
 * File: study/src/study.cpp
*/

#include "study.h"


int main(int argc, char ** argv, char ** env) {
    // The first agrument should be the name of the game we want to play
    char * game_name = NULL;
    bool mp = false;
    if (argc < 2) {
        errno = EINVAL;
        MACRO_LOG_FATAL("Usage: %s name_of_card_game mp", argv[0]);
    }
    /*
    if (argc > 2) {
        mp = true;
        std::cout << "By inputing three arguments you have selected" <<
            " multiplayer mode. This means everytime you take an action" <<
            " the next action will be taken by the other player. There was" <<
            " not enough time for sockets so sorry its splitscreen!" <<
            " (more like share screen) Press enter to continue" << std::endl;
        const int buffer_size = 100;
        char buffer[buffer_size];
        std::cin.getline(buffer, buffer_size);
    }
    */
    game_name = argv[1];
    // Ask study to provide us with an instance of that game
    study::game * game = study::game_from_string(game_name);
    if (game == NULL) {
        MACRO_LOG_FATAL("Sorry we do not have the game \"%s\"", game_name);
    }
    // Create a basic player
    study::player player_one(&std::cout, &std::cin);
    study::player player_two(&std::cout, &std::cin);
    if (mp == true) {
        game->play(2, &player_one, &player_two);
    } else {
        game->play(1, &player_one);
    }
    try {
        // We dont need to do anything in between turns
        while(game->next_turn()) {};
    } catch (...) {
        // Make sure we catch so that if something goes wrong we can free game
    }
    // We have no more use for the game
    MACRO_DELETE_IF_NOT_NULL(game);
    return EXIT_SUCCESS;
}
