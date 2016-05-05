#include "cards.h"

/*
 * Constructor
 */
cards::player_no_ostream::player_no_ostream() {}

/*
 * Destructor
 */
cards::player_no_ostream::~player_no_ostream() throw() {}

/*
 * Describes the error
 */
const char * cards::player_no_ostream::what() const throw() {
    return "No ostream to write to";
}
