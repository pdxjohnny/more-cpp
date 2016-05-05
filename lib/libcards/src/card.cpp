#include <cctype>
#include "cards.h"


/*
 * Create a card which by default is an Ace of Hearts just because we need a
 * default
 */
cards::card::card() : value('A'), suit(cards::SUIT_HEARTS) {}

/*
 * A card cant change its suit or value so it wouldnt make sence to
 * have those be a default value
 */
cards::card::card(char value, char suit) throw(cards::invalid_card_value, cards::invalid_card_suit) : value(value), suit(suit) {
    // Make the value upercase so that comparisons will always work
    this->value = std::toupper(value);
    // Make sure the suit is upercase as well
    this->suit = std::toupper(suit);
    // Make sure that this is a value value for a card, so 1 - 9 and K,Q,J,A
    // 1 will repsresent 10
    if (!((this->value >= '1' && this->value <= '9') ||
                this->value == 'K' || this->value == 'Q' ||
                this->value == 'J' || this->value == 'A')) {
        throw cards::invalid_card_value();
    }
    // Make sure that the suit is valid
    if (!(this->suit == cards::SUIT_HEARTS ||
                this->suit == cards::SUIT_DIMONDS ||
                this->suit == cards::SUIT_SPADES ||
                this->suit == cards::SUIT_CLUBS)) {
        throw cards::invalid_card_suit();
    }
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
bool cards::operator <  (const cards::card & one, const cards::card & two) {
    // Ace is always less than everything but not if its againt itself then it
    // is less than or equal
    if (one.value == 'A' && two.value != 'A') {
        return true;
    }
    if (two.value == 'K' && (one.value == 'Q')) {
        return true;
    }
    // 1 represents 10 because 'A'ce represents 1
    if (two.value == '1' && (one.value >= '2' && one.value <= '9')) {
        return true;
    }
    return (one.value <  two.value);
}
bool cards::operator <= (const cards::card & one, const cards::card & two) {
    return (cards::operator <  (one, two)) || (cards::operator == (one, two));
}
bool cards::operator >  (const cards::card & one, const cards::card & two) {
    return cards::operator <  (two, one);
}
bool cards::operator >= (const cards::card & one, const cards::card & two) {
    return cards::operator <= (two, one);
}
bool cards::operator != (const cards::card & one, const cards::card & two) {
    return !(cards::operator == (one, two));
}
bool cards::operator == (const cards::card & one, const cards::card & two) {
    return (one.value == two.value);
}

/*
 * Displays a card
 */
std::ostream & cards::operator<<(std::ostream & out, cards::card & card) {
    if (card.suit == cards::SUIT_HEARTS || card.suit == cards::SUIT_DIMONDS) {
        out << MACRO_RED;
    } else {
        out << MACRO_CYAN;
    }
    if (card.value == '1') {
        out << "[ 10  " << card.suit << " ]";
    } else {
        out << "[ " << card.value << "   " << card.suit << " ]";
    }
    out << MACRO_RESET;
    return out;
}
