#include <libcards.h>

/*
 * You can to pass an initialized ostream and istream to create a player
 */
cards::player::player(std::ostream & out, std::istream & in) : out_stream(out), in_stream(in) {}

/*
 * Destructor does nothing
 */
cards::player::~player() {}

/*
 * Return our output stream
 */
std::ostream & cards::player::out() {
    return out_stream;
}

/*
 * Return our input stream
 */
std::istream & cards::player::in() {
    return in_stream;
}
