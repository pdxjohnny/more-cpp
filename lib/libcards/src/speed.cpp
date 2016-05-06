#include "cards.h"

/*
 * Create the game
 */
cards::speed::speed() {
    // We are using llls of arrays to store our cards in so lets allocate and
    // fill them with the cards they need
    // Speed has to stacks that are essentially the deck
    const int stacks_needed = 2;
    int i;
    int j;
    // Create the stacks and initialize them to have random cards in them
    for (i = stacks_needed - 1; i >= 0; --i) {
        stacks[i] = new cards::card[cards::SPEED_STACK_SIZE];
        stack_sizes[i] = 0;
        for (j = cards::SPEED_STACK_SIZE - 1; j >= 0; --j) {
            stacks[i][j] = random();
            ++stack_sizes[i];
        }
    }
    // Create the discard arrays there is one discard pile next to each stack
    for (i = stacks_needed - 1; i >= 0; --i) {
        discard[i] = new cards::card[cards::SPEED_DISCARD_SIZE];
        // Make sure there is a card for us to start with
        discard[i][0] = random();
        discard_sizes[i] = 1;
    }
}

/*
 * Clean up the game when its over
 */
cards::speed::~speed() {
    // We are using a lll of arrays to manage our card stacks. In our
    // destructor we need to be sure to free them all
    int i;
    for (i = stacks.size() - 1; i >= 0; --i) {
        MACRO_DELETE_ARRAY_IF_NOT_NULL(stacks[i]);
    }
    for (i = discard.size() - 1; i >= 0; --i) {
        MACRO_DELETE_ARRAY_IF_NOT_NULL(discard[i]);
    }
}

/*
 * Turn asks the player what we should do on this turn
 */
bool cards::speed::turn(cards::player & curr) {
    const int buffer_size = 100;
    char buffer[buffer_size];
    int hand_index = 0;
    int discard_index = 0;
    // If the comunication to the player is closed then we have a problem
    if (curr.in().eof()) {
        return false;
    }
    // Show everyone the cards
    display_all();
    // Show the player their cards
    curr.out() << curr << std::endl;
    // Ask the user what they want to do
    curr.out() << "Action: ";
    memset(buffer, 0, buffer_size);
    curr.in().getline(buffer, buffer_size);
    // Make sure we have enough information to do something. If we do not get
    // any input we take that to mean that the player is stuck and then we wait
    // for both players to be stuck before fliping one of the stack cards onto
    // the discard piles
    if (strnlen(buffer, buffer_size) < 3) {
        return true;
    }
    // The user should input the index of the card in their hand that they
    // would like to use to place on the discard stack that they specify.
    // So Action: 3 0 would place the 4th card in your hand in the first
    // discard pile
    sscanf(buffer, "%d %d", &hand_index, &discard_index);
    // Make sure those indexes are valid
    if (hand_index > 4 || hand_index < 0 || discard_index > 1 || discard_index < 0) {
        return true;
    }
    // Grab the card at that index from the hand and put it on the discard pile
    cards::card add = curr[hand_index];
    cards::card last = discard[discard_index][discard_sizes[discard_index] - 1];
    // Make sure that what the player is trying to put on the discard pile is
    // valid. The card we are putting down has to be one point value different
    // above or below the card it is being set down on. In the case of the Ace
    // and King we need to make sure the correct logic is implemented there
    cards::card ace('A', cards::SUIT_HEARTS);
    cards::card king('K', cards::SUIT_HEARTS);
    // If this is a king and the last was an ace or viseversa then we are ok
    // if that is not the case then just check like normal that all is well, if
    // not then return
    if (!((add == king && last == ace) || (add == ace && last == king) ||
            ((add - last) != 1 && (add - last) != -1))) {
        return true;
    }
    // Display the restuls
    display_all();
    return true;
}

/*
 * Displays the board
 */
void cards::speed::display(std::ostream & out) {
    // Clear any pervious output
    cards::clear(out);
    // Display the stacks and discard piles
    if (stack_sizes[0] > 0) {
        out << cards::CARD_UNKNOWN << "  ";
    } else {
        out << cards::CARD_BLANK << "  ";
    }
    // There should always be something in the discard pile
    out << discard[0][discard_sizes[0] - 1] << "  ";
    out << discard[1][discard_sizes[1] - 1] << "  ";
    // Display the other stack
    if (stack_sizes[1] > 0) {
        out << cards::CARD_UNKNOWN << "  ";
    } else {
        out << cards::CARD_BLANK << "  ";
    }
    out << std::endl << std::endl;
    return;
}
