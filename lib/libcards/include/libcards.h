/*
 * John Andersen
 * File: libcards/include/libcards.h
*/
#include <exception>
#include <liblll.h>

// No card games name is longer than this
#define CARDS_MAX_GAME_NAME_SIZE 100

// namespace cards provides card games and their abstract base class the card
// game. You can play the games that are here or create your own game by
// deriving from cards::game
namespace cards {
    // Card coingtians the value and suit
    class card;
    // The abstract base class
    class game;
    // A deck of cards
    class deck;
    // A hand of cards
    class hand;
    // Methods to play and manage card games
    // Plays a card game
    void play(cards::game &);
    // Returns an instance of the game requested by the string
    cards::game * game_from_string(char * game_name);
    // Constants that are used to play cards
    const char SUIT_HEARTS = 'H';
    const char SUIT_DIMONDS = 'D';
    const char SUIT_SPADES = 'S';
    const char SUIT_CLUBS = 'C';
    // Exceptions
    // invalid_card_value means that the value is not 1 - 9 or K,Q,J,A
    class invalid_card_value;
    // invalid_card_suit means that the suit is invalid, not H,D,S,C
    class invalid_card_suit;

    // Friend funcions
    bool operator <  (const cards::card &, const cards::card &);
    bool operator <= (const cards::card &, const cards::card &);
    bool operator >  (const cards::card &, const cards::card &);
    bool operator >= (const cards::card &, const cards::card &);
    bool operator != (const cards::card &, const cards::card &);
    bool operator == (const cards::card &, const cards::card &);

    // Various card games that this library has already implemented
    class solitare;
};

// If the value given to the card constructor is not a regular card value this
// is thrown
class cards::invalid_card_value : public std::exception {
    public:
        invalid_card_value();
        ~invalid_card_value() throw();
        virtual const char * what() const throw();
};

// If the suit given to the card constructor is not a regular suit this is
// thrown
class cards::invalid_card_suit : public std::exception {
    public:
        invalid_card_suit();
        ~invalid_card_suit() throw();
        virtual const char * what() const throw();
};

class cards::card {
    public:
        // A card cant change its suit or value so it wouldnt make sence to
        // have those be a default value
        card(char value, char suit) throw(cards::invalid_card_value, cards::invalid_card_suit);
        // Copy another card
        card(const card & copy);
        // Destroy the card, no point this wont do anything
        ~card();
        // Copy the cards data
        card & operator=(const card & copy);
        // Checks if we are the same color as another card
        bool same_color(const card & check);
        // Checks if we are the same suit as another card
        bool same_suit(const card & check);
        // Lets us compare our value to that of another card
        friend bool operator <  (const cards::card &, const cards::card &);
        friend bool operator <= (const cards::card &, const cards::card &);
        friend bool operator >  (const cards::card &, const cards::card &);
        friend bool operator >= (const cards::card &, const cards::card &);
        friend bool operator != (const cards::card &, const cards::card &);
        friend bool operator == (const cards::card &, const cards::card &);
    private:
        char value;
        char suit;
};

// cards::hand is a hand of cards. A hand is the cards the player is holding.
// It contains the cards a player can and cant view. For example some games
// like go fish you can always see all your cards. Other games like speed you
// can only have a certain number of cards available to view
class cards::hand : public lll<cards::card> {
    public:
        // Initializes the hand. Some games the hand is a fixed size. If this
        // is the case specify the size, otherwise spcifiy 0 for a hand of
        // variable size. The size of the hand you can see that is. The cards
        // you cant see but are still in your posession are
        hand();
        // Gets rid of the hand
        ~hand();
        // Draws a card from the deck and places it in the hand. A callback can
        // also be provided to decide if you want to place it into your cards
        // you can see or the cards you cant see. The callback should return
        // CARDS_DRAW_TO_VISABLE or CARDS_DRAW_TO_HIDDEN. anything else will
        // throw a no where to draw to error.
        char draw(cards::deck &, int (*)(char card));
    private:
        // Keep track of the card that we cant see
        lll<cards::card> not_visable;
};

// cards::deck is a deck of cards. A deck of cards is organized by suite. A deck
// also can be shuffled so that it can be used for a card game
class cards::deck {
    public:
        // Initailizes the deck
        deck();
        // Gets rid of the deck
        ~deck();
        // Lets you access a random card from the deck. That card will not be
        // available to access again until you have shuffled the deck. If there
        // are no more cards to be played random returns -1 which is of course
        // not a real card. Otherwise it will return the ASCII value of the
        // card. That way its easier to diplay to the user
        char random();
        // Shuffling the deck makes it so all the cards can be accessed by
        // random again
        void shuffle();
};

// cards::game is the base class with card games should be derived from. It
// tells you what methods you must implement if you want to use the game_
// functions under the cards namespace. Every card game has a deck of cards
// there for a card game is a deck plus whatever you to to the deck to play the
// game
class cards::game : public cards::deck {
};

// This is the game of solitare
#define CARDS_GAME_SOLITARE "solitare"
class cards::solitare : public cards::game {
};
