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
    // If there is not enough to work with this was a noop
    if (strnlen(buffer, buffer_size) < 5) {
        return true;
    }
    // We have enough info to work with, user can move with place index to
    // place index with the syntax "C0 C6". This would move the card in column
    // zero to be the last card in column 6, if it can otherwise it will do
    // nothing. T for top to S for suit woulf move a card from the top three
    // into the suit area, remoember you can only take the rightmost card from
    // the top. T S3, moves the top card into the last suit position in the top
    // row
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
    int i = 0;
    int j = 0;
    int longest_column = 0;
    // Display the cards to choose from
    for (i = 0; i < 3; ++i) {
        if (choose.size() > i) {
            out << choose[i] << "  ";
        } else {
            out << cards::CARD_BLANK << "  ";
        }
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
                out << cards::CARD_BLANK << "  ";
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
    // Make sure we have enough cards to give from the deck before we call
    // random
    if (size() > 0) {
        choose[0] = random();
    }
    if (size() > 0) {
        choose[1] = random();
    }
    if (size() > 0) {
        choose[2] = random();
    }
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
