#include "cards.h"

/*
 * Constructor
 */
cards::invalid_card_value::invalid_card_value() {}

/*
 * Destructor
 */
cards::invalid_card_value::~invalid_card_value() throw() {}

/*
 * Describes the error
 */
const char * cards::invalid_card_value::what() const throw() {
    return "Value for card was invalid";
}
