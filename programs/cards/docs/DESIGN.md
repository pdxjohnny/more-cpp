
                            DESIGN DOC CARD GAMES
                                John Andersen
                                  04/26/2016

    This program allows users to play various card games. Card games all have
similar functionality. They all have a deck and players. Players have hands.
For some games you can see all the cards in your hand other games you can only
see a few but you have more than you can see. A deck of cards is 52 cards.
Decks can be shuffled which is when all the cards are reordered randomly. This
way every time a card is drawn from the deck its a random card. Card games also
my need to manage how the cards are distributed. Perhaps there are several
piles of cards that the user is interacting with, the game should ask the user
which card to put in which pile. Players need to be controlled by someone or
something. It would be nice to provide the card game with a generic player that
can do things suchs as provide input or be sent information on how the game is
going such as the other player did x and the cards now look like y. This player
could be a real person or it could be something that programaticly makes
desicions just as a real person would do. That way the player could play
against the program. The best way to do this would probably be to have a
seperate ai player for each game. Unless we want to use TensorFlow and see how
good we can get at playing cards :) That way the ai player only needs to know
how to play one game and we instanciate different ais to play against for
different games.
    The requirements for this program are that it implements the game of
solitre and users an array of doubly linked lists and a linked list of arrays.
This is of course perfect for solitare. There are a defined number of stacks
that hold the King through Ace cards going down which would be great as an
array of doubly linked lists because you need to remove and reattach parts of
those onto different columns and they could detach in the middle. Having a
previous pointer here is nice because we dont have to drag it along with us
when we want to remove part of the column. The linked list of arrays is great
because the top area of a solitare game is where you store all cards of one
suit. There are at most 13 cards of a suit so an array works fine being that
its size doesnt change once allocated.
    I dont know many card games but the other one I thought would be fun the
implement is speed. This would be unfair to play against an ai because the
computer would always be faster but I could just add a variable timer that
makes it seem to the end user that the ai is thinking. But obviously the fun to
be had with this program really lies in deriving from ostream and istream or
hopefully iostream to implement the players. This way they could be accepting
input from the game just like if the game were to ask for input from cin. The
end users player class would simply be cin and cout but the possibilies are now
limitless for everything else. At the least it would take the data send to it
and store it in a queue where the ai could ask for the most recent string sent
to it do some string compares or whatnot on it and then send back a reply. Of
course what I really want to do is not have an ai at all and just listen on a
port which the other player can connect to via tcp. They could then play with
bash! exec 3<>/dev/tcp/localhost/56784, or netcat! nc locahost:56784. Ya that
would be fun I have been working on it and will definatly do that if I can
properly inherit from iostream. Other than that I will dirive game from deck
the various games from game player types from iostream / streambuf I hope I can
figure it out.
