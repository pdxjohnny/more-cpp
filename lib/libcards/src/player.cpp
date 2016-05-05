#include <libcards.h>

/*
 * Create a player with no input or output
 */
cards::player::player() : out_stream(NULL), in_stream(NULL) {}

/*
 * You can to pass an initialized ostream and istream to create a player
 */
cards::player::player(std::ostream * out, std::istream * in) : out_stream(out), in_stream(in) {}

/*
 * Destructor does nothing
 */
cards::player::~player() {}

/*
 * Copying a player just copies the pointers to the streams it is using because
 * it cannot duplicate them
 */
cards::player & cards::player::operator=(const cards::player & copy) {
    this->out_stream = copy.out_stream;
    this->in_stream = copy.in_stream;
    return *this;
}

/*
 * Return our output stream
 */
std::ostream & cards::player::out() throw(cards::player_no_ostream) {
    // If someone tries to access our output before we have an output then we
    // need to through an error
    if (out_stream == NULL) {
        throw cards::player_no_ostream();
    }
    return *out_stream;
}

/*
 * Return our input stream
 */
std::istream & cards::player::in() throw(cards::player_no_istream) {
    // If someone tries to access our input before we have an input then we
    // need to through an error
    if (in_stream == NULL) {
        throw cards::player_no_istream();
    }
    return *in_stream;
}
