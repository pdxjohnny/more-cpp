#include "cards.h"

cards::game * cards::game_from_string(char * game_name) {
    if (0 == strncmp(CARDS_GAME_SOLITARE, game_name, CARDS_MAX_GAME_NAME_SIZE)) {
        return new cards::solitare();
    } else if (0 == strncmp(CARDS_GAME_SPEED, game_name, CARDS_MAX_GAME_NAME_SIZE)) {
        return new cards::speed();
    }/* else if (0 == strncmp(CARDS_GAME_, game_name, CARDS_MAX_GAME_NAME_SIZE)) {
        return new cards::();
    }*/
    return NULL;
}
