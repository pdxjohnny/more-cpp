#include <libcards.h>

/*
 * Constructor
 */
cards::invalid_card_suit::invalid_card_suit() {}

/*
 * Destructor
 */
cards::invalid_card_suit::~invalid_card_suit() throw() {}

/*
 * Describes the error
 */
const char * cards::invalid_card_suit::what() const throw() {
    return "Suit for card was invalid";
}
