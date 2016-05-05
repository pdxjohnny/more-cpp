#include "cards.h"

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
bool cards::solitare::turn(cards::player & curr) {
    const int buffer_size = 100;
    char buffer[buffer_size];
    // If the comunication to the player is closed then we have a problem
    if (curr.in().eof()) {
        return false;
    }
    display_all();
    // Ask the user what they want to do
    curr.out() << "Action: ";
    curr.in().getline(buffer, buffer_size);
    // Display the restuls
    display_all();
    return true;
}

/*
 * Displays the board
 */
void cards::solitare::display(std::ostream & out) {
    // Clear any pervious output
    cards::clear(out);
    // Display the cards to choose from
    int i;
    int j;
    int choose_size = choose.size();
    for (i = 0; i < choose_size; ++i) {
        out << choose[i] << "  ";
    }
    out << std::endl;
    // Ouput the top card on the top stacks
    out << "                    ";
    for (i = 0; i < 4; ++i) {
        if (top[i].size() > 0) {
            out << top[i][top[i].size() - 1] << "  ";
        } else {
            out << "        ";
        }
    }
    out << std::endl;
    // Ouput all of the columns
    for (i = 0; i < 4; ++i) {
        for (j = 0; j < 4; ++j) {
            if (top[i].size() > 0) {
                out << top[i][top[i].size() - 1] << "  ";
            } else {
                out << "        ";
            }
        }
    }
    out << std::endl;
    return;
}
