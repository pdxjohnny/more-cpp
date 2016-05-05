#include "cards.h"
#include <sstream>

class test_cards_game_player : public cards::player {
    public:
        test_cards_game_player(std::ostream * o, std::istream * i) : cards::player::player(o, i), called(0) {}
        int called;
};

class test_cards_game : public cards::game {
    protected:
        bool turn(cards::player & p) {
            test_cards_game_player * p_count = (test_cards_game_player *)&p;
            ++p_count->called;
            return true;
        }
};

int test_cards_game_player_rotation() {
    test_cards_game game;
    // These are just for testing
    std::ostringstream p1_out;
    std::istringstream p1_in;
    test_cards_game_player p1(&p1_out, &p1_in);
    std::ostringstream p2_out;
    std::istringstream p2_in;
    test_cards_game_player p2(&p2_out, &p2_in);
    std::ostringstream p3_out;
    std::istringstream p3_in;
    test_cards_game_player p3(&p3_out, &p3_in);
    // Pass all our players to the game
    game.play(3, &p1, &p2, &p3);
    // Go for 6 turns so each player should have taken two turns at the end
    const int turns = 6;
    int i;
    for (i = turns - 1; i >= 0; --i) {
        bool keep_going = game.next_turn();
        MACRO_TEST_EQ(keep_going, true);
    }
    MACRO_TEST_EQ(p1.called, 2);
    MACRO_TEST_EQ(p2.called, 2);
    MACRO_TEST_EQ(p3.called, 2);
    return EXIT_SUCCESS;
}
