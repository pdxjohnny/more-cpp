#include "cards.h"

/*
 * Constructor
 */
cards::player_no_istream::player_no_istream() {}

/*
 * Destructor
 */
cards::player_no_istream::~player_no_istream() throw() {}

/*
 * Describes the error
 */
const char * cards::player_no_istream::what() const throw() {
    return "No istream to write to";
}
