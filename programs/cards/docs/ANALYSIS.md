Card Games
---

    This program was good I didnt get to waht I was so excited about doing with
deriving from i and o stream classes so I didnt make it to multiplayer which is
a bummer. The game speed I made would be much more fun with another person but
I just didnt have time to wrap a socket in a streambuf and all that. I started
but then I had to acctually write the program and I realized I didnt have time
for that.
    I implemented solitare and speed as my card games and with dynamic
binding its easy as pie to implement more! I really ended up spending the
majority of my time on the linked list class. I really wanted to get around the
fact that you cant have virtual functions in a templated class. My solution was
to have a base classes that did everything but access and hold the data then
just derive and make a method to access the data the derived node is holding.
It works like a charm. The whole point of it was that I wanted to make my dll
class a few lines but I dont have anymore time so I just copied the lll and
changed the funciton internals. Probably would have only taken a few more
minutes to do waht I had planed originaly where dll node and dll derive from
lll node and lll but I cant afford to spend more time on it. I put all the
cards stuff in a namespace so that its organized. I didnt bother trying to put
lll in a namespcae because I think there was something that happened where it
complained about having a templated class in a namespace and it wasnt worth the
time. Another thing I ran into was having the errors of classes in the cards
namespace be classes within the classes they are errors for. It didnt work so I
just put them as error classes in the namespace, again no time to figure it
out.
    Implementing the friend comparison operators was fun I got it down to to
that acctually do anything and the rest just call those two, so that was nifty.
I mentioned errors alreay but yes I created some errors, even teseted that they
were thrown, all that good stuff. As suggested for the ostream extraction
operator I used a virtual display method and that worked well. The player class
I played around a bit with trying to decide wether I wanted to have the streams
as references put in at initialization or pointers and I went with pointers
because as far as I could tell the assingment operator cant assinge to refernce
data members, they can only be assinged in an initialization list. I had lots
of fun with the asingment operators and making them virtual in places and
testing that the correct assingment operator had been called. Those tests are
int liblll I believe.
    Lets be honset here we all know the most fun part of this was outputing the
cards in colors. Colors never get old. Solitare I didnt end up doing where you
can move a stack from anywhere to anywere else, it only supports moving the
last card on the stack. This made it a little of a bummer when playing but I
guess you just have to be supper good to play this version. I could have done
that but the reason I didnt was because I would have to put more time into
parsing ht user input to find which column and row they wanted and if I did
that then I would have to write a test for it and then it would have been at
least an hour to do all that.
    Overall this was much better than the first program because we acctually
did something! We made a game and who doesnt love making games! And colors are
great. You can find videos of how to play in the README.md file. Moral of this
was that virtual functions are great and friends are great too so long as you
use them with virtual functions so that you dont have to implement that friend
for the child class. And playing with the `va_args` stuff was fun too.
