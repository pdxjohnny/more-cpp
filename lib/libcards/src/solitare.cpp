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
    // If there are no more cards in tho top then try to take soem from the
    // deck and put them there
    if (top.size() < 1) {
        choose3();
    }
    // Show everyone the cards
    display_all();
    // Ask the user what they want to do
    curr.out() << "Action: ";
    memset(buffer, 0, buffer_size);
    curr.in().getline(buffer, buffer_size);
    // Make sure we have enough for a one character action
    if (strnlen(buffer, buffer_size) < 1) {
        return true;
    }
    // Handle one character operations like N for New top to choose from
    switch (std::toupper(buffer[0])) {
        case 'N':
            choose3();
            break;
        case 'S':
            // Shuffling restarts the game
            shuffle();
            break;
        default:
            // FIXME this is horrendous but I dont have time
            // If there is not enough to work with for other actions this was a noop
            if (strnlen(buffer, buffer_size) < 4) {
                return true;
            }
            // We have enough info to work with, user can move with place index to
            // place index with the syntax "C0 C6". This would move the card in column
            // zero to be the last card in column 6, if it can otherwise it will do
            // nothing. T for top to S for suit woulf move a card from the top three
            // into the suit area, remoember you can only take the rightmost card from
            // the top. T S3, moves the top card into the last suit position in the top
            // row
            // Move from Top to Suits
            if (std::toupper(buffer[0]) == 'T' && strchr(buffer, 'S') != NULL &&
                    strlen(strchr(buffer, 'S')) > 1) {
                int suits_index = atoi(&(strchr(buffer, 'S')[1]));
                // We only have 4 suits
                if (suits_index > 3) {
                    return true;
                }
                cards::card add = top[top.size() - 1];
                // If we could not add then go to the next turn
                if (!move_suit(add, suits_index)) {
                    return true;
                }
                // Since it has been added to that suit remove it from top
                top.remove(top.size() - 1);
            } else if (std::toupper(buffer[0]) == 'C' && strchr(buffer, 'S') != NULL &&
                    strlen(strchr(buffer, 'S')) > 1) {
                int from_index = atoi(&(strchr(buffer, 'C')[1]));
                int suits_index = atoi(&(strchr(buffer, 'S')[1]));
                // We only have 4 suits
                if (suits_index > 6 || from_index > 6) {
                    return true;
                }
                cards::card add = column[from_index][column[from_index].size() - 1];
                // If we could not add then go to the next turn
                if (!move_suit(add, suits_index)) {
                    return true;
                }
                // Since it has been added to that suit remove it from column
                column[from_index].remove(column[from_index].size() - 1);
                // If we removed everything then we need to make the next
                // hidden card visable
                make_visable(from_index);
            } else if (std::toupper(buffer[0]) == 'C' && strchr(&buffer[1], 'C') != NULL &&
                    strlen(strchr(&buffer[1], 'C')) > 1) {
                // Move from Top to Column
                int from_index = atoi(&(strchr(buffer, 'C')[1]));
                int column_index = atoi(&(strchr(&buffer[1], 'C')[1]));
                // We only have 7 column
                if (column_index > 6 || from_index > 6) {
                    return true;
                }
                cards::card add = column[from_index][column[from_index].size() - 1];
                // If we could not add then go to the next turn
                if (!move_column(add, column_index)) {
                    return true;
                }
                // Since it has been added to that suit remove it from top
                column[from_index].remove(column[from_index].size() - 1);
                // If we removed everything then we need to make the next
                // hidden card visable
                make_visable(from_index);
            } else if (std::toupper(buffer[0]) == 'T' && strchr(buffer, 'C') != NULL &&
                    strlen(strchr(buffer, 'C')) > 1) {
                // Move from Top to Column
                int column_index = atoi(&(strchr(buffer, 'C')[1]));
                // We only have 7 column
                if (column_index > 6) {
                    return true;
                }
                cards::card add = top[top.size() - 1];
                // If we could not add then go to the next turn
                if (!move_column(add, column_index)) {
                    return true;
                }
                // Since it has been added to that suit remove it from top
                top.remove(top.size() - 1);
            }
            break;
    }
    // If there are no more cards in tho top then try to take soem from the
    // deck and put them there
    if (top.size() < 1) {
        choose3();
    }
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
    int longest_column = 20;
    // Display the cards to choose from
    for (i = 0; i < 3; ++i) {
        if (top.size() > i) {
            out << top[i] << "  ";
        } else {
            out << cards::CARD_BLANK << "  ";
        }
    }
    // Ouput the suits card on the suits stacks
    for (i = 0; i < 4; ++i) {
        if (suits[i].size() > 0) {
            out << suits[i][suits[i].size() - 1] << "  ";
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
 * Populates the top cards
 */
void cards::solitare::choose3() {
    // Put any cards in top back into the deck
    int top_size = top.size();
    int i;
    for (i = 0; i < top_size; ++i) {
        this->operator[](this->size()) = top[i];
    }
    // Remove the cards from top
    top.remove_all();
    // Draw three new random cards from the deck and put them in top
    // Make sure we have enough cards to give from the deck before we call
    // random
    if (size() > 0) {
        top[0] = random();
    }
    if (size() > 0) {
        top[1] = random();
    }
    if (size() > 0) {
        top[2] = random();
    }
}

/*
 * Populates the columns
 */
void cards::solitare::populate_columns() {
    int i;
    int j;
    for (i = 6; i >= 0; --i) {
        column_hidden[i].remove_all();
        for (j = i - 1; j >= 0; --j) {
            column_hidden[i][j] = random();
        }
    }
    for (i = 6; i >= 0; --i) {
        column[i].remove_all();
        column[i][0] = random();
    }
}

/*
 * Shuffling restarts the game
 */
void cards::solitare::shuffle() {
    cards::deck::shuffle();
    suits[0].remove_all();
    suits[1].remove_all();
    suits[2].remove_all();
    suits[3].remove_all();
    choose3();
    populate_columns();
}

/*
 * Moves a card into a suit but if that doesnt work it returns false
 */
bool cards::solitare::move_suit(cards::card & add, int suits_index) {
    // If there are no cards in that slot yet we can put it there and be
    // done otherwise we have to make sure its a vaild placment
    if (suits[suits_index].size() > 0) {
        // Make sure that the card we are putting it on is exaxtly one less
        // than this card and the same suit
        cards::card suit_top = suits[suits_index][suits[suits_index].size() - 1];
        if (!suit_top.same_suit(add) || (add - suit_top) != 1) {
            // Either its not the same suit or it is not one above the card we
            // are trying to put it on
            return false;
        }
    } else {
        // If this is going to be the first into that suit spot it must be
        // an Ace
        cards::card must_be_ace('A', cards::SUIT_HEARTS);
        if (add != must_be_ace) {
            return false;
        }
    }
    // All is well so add the card
    suits[suits_index][suits[suits_index].size()] = add;
    return true;
}

/*
 * Moves a card into a column but if that doesnt work it returns false
 */
bool cards::solitare::move_column(cards::card & add, int column_index) {
    // If there are no cards in that slot yet we can put it there and be
    // done otherwise we have to make sure its a vaild placment
    if (column[column_index].size() > 0) {
        // Make sure that the card we are putting it on is exaxtly one more
        // than this card and not the same color
        cards::card column_top = column[column_index][column[column_index].size() - 1];
        if (column_top.same_color(add) || (column_top - add) != 1) {
            // Either its not the same suit or it is not one above the card we
            // are trying to put it on
            return false;
        }
    } else {
        // If this is going to be the first into that suit spot it must be
        // a King
        cards::card must_be_king('K', cards::SUIT_HEARTS);
        if (add != must_be_king) {
            return false;
        }
    }
    // All is well so add the card
    column[column_index][column[column_index].size()] = add;
    return true;
}

/*
 * Checks if there is anything left in the column or if it is time to make the
 * hidden column visable. Index is the index of the column to check on.
 */
void cards::solitare::make_visable(int index) {
    // If there is still some visable or non that are hidden we dont have
    // anything to do
    if (column[index].size() > 1 || column_hidden[index].size() < 1) {
        return;
    }
    column[index][0] = column_hidden[index][column_hidden[index].size() - 1];
    column_hidden[index].remove(column_hidden[index].size() - 1);
}
