/*
 * John Andersen
 * File: libcards/include/libcards.h
*/

// namespace cards provides card games and their abstract base class the card
// game. You can play the games that are here or create your own game by
// deriving from cards::game
namespace cards {
    // Resets a card game
    // The abstract base class
    class game;
    // A deck of cards
    class deck;
    // A hand of cards
    class hand;
    // Methods to play and manage card games
    // Plays a card game
    void play(cards::game &);
};

// cards::hand is a hand of cards. A hand is the cards the player is holding.
// It contains the cards a player can and cant view. For example some games
// like go fish you can always see all your cards. Other games like speed you
// can only have a certain number of cards available to view
class cards::hand {
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
