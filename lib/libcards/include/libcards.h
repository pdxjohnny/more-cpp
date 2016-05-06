/*
 * John Andersen
 * File: libcards/include/libcards.h
*/
#include <exception>
#include <iostream>
#include <cstdarg>
#include <liblll.h>
#include <libdll.h>

// No card games name is longer than this
#define CARDS_MAX_GAME_NAME_SIZE 100

// namespace cards provides card games and their abstract base class the card
// game. You can play the games that are here or create your own game by
// deriving from cards::game
namespace cards {
    // Card coingtians the value and suit
    class card;
    // A player just holds pointers to the istream and ostream they can be
    // interfaced through
    class player;
    // The abstract base class
    class game;
    // A deck of cards
    class deck;
    // A hand of cards
    class hand;
    // Methods to play and manage card games
    // Plays a card game
    void play(cards::game &);
    // Prints a whole bunch of lines to clear the screen
    void clear(std::ostream &);
    // Returns an instance of the game requested by the string
    cards::game * game_from_string(char * game_name);
    // Constants that are used to play cards
    const char SUIT_HEARTS = 'H';
    const char SUIT_DIMONDS = 'D';
    const char SUIT_SPADES = 'S';
    const char SUIT_CLUBS = 'C';
    const char CARD_UNKNOWN[] = MACRO_YELLOW "[#######]" MACRO_RESET;
    const char CARD_BLANK[] = "         ";
    // Exceptions
    // invalid_card_value means that the value is not 1 - 9 or K,Q,J,A
    class invalid_card_value;
    // invalid_card_suit means that the suit is invalid, not H,D,S,C
    class invalid_card_suit;
    // In case there is no i or o stream
    class player_no_ostream;
    class player_no_istream;

    // Friend funcions
    int  operator -  (const cards::card &, const cards::card &);
    bool operator <  (const cards::card &, const cards::card &);
    bool operator <= (const cards::card &, const cards::card &);
    bool operator >  (const cards::card &, const cards::card &);
    bool operator >= (const cards::card &, const cards::card &);
    bool operator != (const cards::card &, const cards::card &);
    bool operator == (const cards::card &, const cards::card &);

    // Displays a game, up to that game to implement game::display
    // this is for showing the user the current cards
    std::ostream & operator << (std::ostream &, cards::game &);
    std::ostream & operator << (std::ostream &, cards::hand &);

    // Various card games that this library has already implemented
    class solitare;
    class speed;

    // Game spcific constants
    const int SPEED_STACK_SIZE = 15;
    const int SPEED_DISCARD_SIZE = 52;
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

// A card has a suit and a value and can be compared with operators to compare
// its value to other cards. It also has methods to find out if it is in the
// same suit or color as another card
class cards::card {
    public:
        card();
        // Normally a card is initialized to something
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
        // Lets us see what the cards iniger value is
        int to_int() const;
        // Lets us compare our value to that of another card
        friend int  operator -  (const cards::card &, const cards::card &);
        friend bool operator <  (const cards::card &, const cards::card &);
        friend bool operator <= (const cards::card &, const cards::card &);
        friend bool operator >  (const cards::card &, const cards::card &);
        friend bool operator >= (const cards::card &, const cards::card &);
        friend bool operator != (const cards::card &, const cards::card &);
        friend bool operator == (const cards::card &, const cards::card &);
        // Outputs the card
        friend std::ostream & operator << (std::ostream &, cards::card &);
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
        // Draws a card from the deck and places it in the hand that is visable
        cards::card & draw_visable(cards::deck &);
        // Draws a card and places it in the not_visable cards we own
        cards::card & draw_not_visable(cards::deck &);
        // Sets num_visable parameter
        virtual void set_num_visable(int num);
        // We want to replenish the visable hand with the not_visable hand when
        // to get below whatever number is applicable
        virtual bool remove(int index);
        // Displays the hand
        virtual void display(std::ostream &);
        // Outputs the hand
        friend std::ostream & operator << (std::ostream &, cards::hand &);
    private:
        // Keep track of the card that we cant see
        lll<cards::card> not_visable;
        // How many cards should be visable at a time
        int num_visable;
};

// cards::deck is a deck of cards. A deck of cards is organized by suite. A deck
// also can be shuffled so that it can be used for a card game
class cards::deck : public lll<cards::card> {
    public:
        // Initailizes the deck
        deck();
        // Gets rid of the deck
        ~deck();
        // Lets you access a random card from the deck. That card will not be
        // available to access again until you have shuffled the deck. If there
        // are no more cards to be played random throws a no more cards
        // exception. We return by value because the card will be removed from
        // the deck and if we were to return by refernece the card would be no
        // longer available
        cards::card random();
        // Shuffling the deck makes it so all the cards can be accessed by
        // random again
        void shuffle();
};

// Errors for player
class cards::player_no_ostream : public std::exception {
    public:
        player_no_ostream();
        ~player_no_ostream() throw();
        virtual const char * what() const throw();
};

class cards::player_no_istream : public std::exception {
    public:
        player_no_istream();
        ~player_no_istream() throw();
        virtual const char * what() const throw();
};

// A player contains an istream and ostream which game can use to interact with
// that player a player is a hand of cards as well because a player without a
// hand of cards cant play cards
class cards::player : public cards::hand {
    public:
        player();
        player(std::ostream *, std::istream *);
        virtual ~player();
        // Copy a player
        player & operator=(const player & copy);
        // Provides people with access to our streams
        virtual std::ostream & out() throw(cards::player_no_ostream);
        virtual std::istream & in() throw(cards::player_no_istream);
        // If the player is unable to take their turn then this flag should be
        // set so that the game can figure out how to resolve the deadlock
        bool is_stuck();
        bool stuck(bool set);
    private:
        // So we can keep track of the streams we are using
        std::ostream * out_stream;
        std::istream * in_stream;
        // Player stuck
        bool stuck_status;
};

// cards::game is the base class with card games should be derived from. It
// tells you what methods you must implement if you want to use the game_
// functions under the cards namespace. Every card game has a deck of cards
// there for a card game is a deck plus whatever you to to the deck to play the
// game
class cards::game : public cards::deck {
    public:
        game();
        virtual ~game();
        // Play needs to be given the primary player and then it will ask how
        // who you want to play against, if applicable to that game. A player
        // is just an istream and an ostream so we can interact with them.
        // Play should return true if it is possible to play the game.
        // when games play is called it adds it to the list of players in
        // game.players
        virtual bool play(int num_players, ...);
        virtual void player_setup(cards::player *);
        // next_turn should be called until it returns false. This way you can
        // call play to set up the game then you call next_turn to have the
        // next player take their turn
        bool next_turn();
        // Displays the game to all players, usefull if you want to show it to
        // everyone as soon as one player does something
        virtual void display_all();
        // Displays the game. This should be overridden or else it wont display
        // anything
        virtual void display(std::ostream &);
        // Displays a game, up to that game to implement game::display
        // this is for showing the user the current cards
        friend std::ostream & operator << (std::ostream &, cards::game &);
        // Lets the game know if everyone is stuck
        bool all_players_stuck();
    protected:
        // turn is called by next_turn which manages which players turn it is
        // turn needs to be implemented by the game deriving from game because
        // it should interact with the user to get their action for this turn.
        // If turn ever returns false then that signals to next_turn that it
        // should return false and the game will be over
        virtual bool turn(player &) = 0;
    private:
        // Becuase this is an abstract base class putting this data mamber in
        // protected allows us to avoid putting it in every other class that
        // uses players. Because we might need to add to the players or remove
        // from the players in another play implementation
        lll<cards::player *> players;
        // This keeps track of which players turn it is
        int current_player;
};

// This is the game of solitare
#define CARDS_GAME_SOLITARE "solitare"
class cards::solitare : public cards::game {
    public:
        solitare();
        ~solitare();
        // We only need to implement turn because game sets up a single player
        // for us and that is all we need
        bool turn(player &);
        // Show the board
        void display(std::ostream &);
    private:
        // Chooses3 cards from the deck the be the cards we can move
        void choose3();
        // Populates teh columsn for the initail setup
        void populate_columns();
        // Shuffling restarts the game
        void shuffle();
        // Moves a card to suits and returns true if the movement was valid
        bool move_suit(cards::card &, int suit_index);
        // Moves a card to a column and returns true if the movement was valid
        bool move_column(cards::card &, int column_index);
        // Makes the hidden cards visable
        void make_visable(int index);
        // Solitare displays three cards at the top of the board which you can
        // choose to put in the columns of to the top
        dll<cards::card> top;
        // The four top coloums for each suit
        dll<cards::card> suits[4];
        // The columns of the solitare board that we can access
        dll<cards::card> column[7];
        // The cards the get hidden under the other cards
        dll<cards::card> column_hidden[7];
};

// This is the game of speed
#define CARDS_GAME_SPEED "speed"
class cards::speed : public cards::game {
    public:
        speed();
        ~speed();
        // We only need to implement turn because game sets up a single player
        // for us and that is all we need
        bool turn(player &);
        // Show the board
        void display(std::ostream &);
    protected:
        void player_setup(cards::player * player);
    private:
        // Fixes when all players are stuck. Takes cards off both stacks and
        // puts them in to the discard piles
        void stack_to_discard();
        // Speed has too stacks that are essentially booth the deck. There is
        // really no reason to do it the way I am going to other than that I
        // have to use a lll of arrays. I am just going to fill each of them
        // from the deck to initialize them
        lll<cards::card *> stacks;
        lll<cards::card *> discard;
        // Because they are arrays we dont want to go past the end of them so
        // when they are allocated we will keep track of their length here
        int stack_sizes[2];
        int discard_sizes[2];
};
