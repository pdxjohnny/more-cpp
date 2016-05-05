#include <cctype>
#include <libcards.h>


/*
 * A card cant change its suit or value so it wouldnt make sence to
 * have those be a default value
 */
cards::card::card(char value, char suit) : value(value), suit(suit) {
    // Make sure that this is a value value for a card, so 2 - 9 and 
    // Make the value upercase so that comparisons will always work
    this->value = std::toupper(value);
}

/*
 * Copy another card
 */
cards::card::card(const card & copy) : value(copy.value), suit(copy.suit) {}

/*
 * Destroy the card, no point this wont do anything as it is just two chars
 */
cards::card::~card() {}

/*
 * Copy the cards data
 */
cards::card & cards::card::operator=(const card & copy) {
    value = copy.value;
    suit = copy.suit;
    return *this;
}

/*
 * Checks if we are the same color as another card
 */
bool cards::card::same_color(const card & check) {
    if ((suit == cards::SUIT_HEARTS || suit == cards::SUIT_DIMONDS) &&
            (check.suit == cards::SUIT_HEARTS || check.suit == cards::SUIT_DIMONDS)) {
        return true;
    }
    if ((suit == cards::SUIT_SPADES || suit == cards::SUIT_CLUBS) &&
            (check.suit == cards::SUIT_SPADES || check.suit == cards::SUIT_CLUBS)) {
        return true;
    }
    return false;
}

/*
 * Checks if we are the same suit as another card
 */
bool cards::card::same_suit(const card & check) {
    return (suit == check.suit);
}

/*
 * Lets us compare our value to that of another card
 */
bool cards::operator <  (const cards::card & first, const cards::card & second) {
    return (first.value <  second.value);
}
bool cards::operator <= (const cards::card & first, const cards::card & second) {
    return (first.value <= second.value);
}
bool cards::operator >  (const cards::card & first, const cards::card & second) {
    return (first.value >  second.value);
}
bool cards::operator >= (const cards::card & first, const cards::card & second) {
    return (first.value >= second.value);
}
bool cards::operator != (const cards::card & first, const cards::card & second) {
    return (first.value != second.value);
}
bool cards::operator == (const cards::card & first, const cards::card & second) {
    return (first.value == second.value);
}
