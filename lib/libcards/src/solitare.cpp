#include "cards.h"

/*
 * Create the game
 */
cards::solitare::solitare() {
    choose3();
    populate_columns();
}

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
    memset(buffer, 0, buffer_size);
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
    int i = 0;
    int j = 0;
    int longest_column = 0;
    int choose_size = choose.size();
    for (i = 0; i < choose_size; ++i) {
        out << choose[i] << "  ";
    }
    // Ouput the top card on the top stacks
    for (i = 0; i < 4; ++i) {
        if (top[i].size() > 0) {
            out << top[i][top[i].size() - 1] << "  ";
        } else {
            out << cards::CARD_UNKNOWN << "  ";
        }
    }
    out << std::endl;
    out << std::endl;
    // Find the longest column
    for (i = 0; i < 7; ++i) {
        int hidden_and_viewable = column_hidden[i].size() + column[i].size();
        if (hidden_and_viewable > longest_column) {
            longest_column = hidden_and_viewable;
        }
    }
    // Ouput all of the hidden columns
    for (i = 0; i < longest_column; ++i) {
        for (j = 0; j < 7; ++j) {
            if (column_hidden[j].size() > i) {
                out << cards::CARD_UNKNOWN << "  ";
            } else if (column[j].size() > (i - column_hidden[j].size())) {
                out << column[j][i - column_hidden[j].size()] << "  ";
            } else {
                out << "           ";
            }
        }
        out << std::endl;
    }
    out << std::endl;
    return;
}

/*
 * Populates the choose cards
 */
void cards::solitare::choose3() {
    // Put any cards in choose back into the deck
    int choose_size = choose.size();
    int i;
    for (i = 0; i < choose_size; ++i) {
        this->operator[](this->size()) = choose[i];
    }
    // Remove the cards from choose
    choose.remove_all();
    // Draw three new random cards from the deck and put them in choose
    choose[0] = random();
    choose[1] = random();
    choose[2] = random();
}

/*
 * Populates the columns
 */
void cards::solitare::populate_columns() {
    int i;
    int j;
    for (i = 6; i >= 0; --i) {
        for (j = i - 1; j >= 0; --j) {
            column_hidden[i][j] = random();
        }
    }
    for (i = 6; i >= 0; --i) {
        column[i][0] = random();
    }
}
