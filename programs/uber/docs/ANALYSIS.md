Analysis of Uber Clone
---

    This program required lots of data. It is essensially a bunch of parsing in
and spiting out strings. Lots of the data that we needed did not get used
exepect to display it back to the user. Address data for example, is useless
unless we were to make a query to Open Street Maps or some maping service to get
the distance between to addresses. This meant that the only information we
really cared about was the latitude and longitude so that we could calculate
the distance as the crow flys between points. Time to drive the route is
another example of the same issue. It is dependent on the route between the two
locations, therefore any time given by the user wouldnt make sense. The user is
not a driver and wouldnt know how long it take to get there anyway. The only
way to get that information is from an external service.
    I was able to have only one "has a" relationship. Everything else was
derived from each other. This made it so I needed very few wrapper functions.
Unless you consider the loading and unloading of data, `to_string` and
`from_string` to be wrappers. The abundence of to and from string methods was
in my opinion unavoidable, as the point was to have different classes be in
charge of different data. Otherwise it could have all been one, but that would
not have been OOP. The end user needs to interact with every data type when
they request the ride. If I had chosen to take user input from stdin in a
nicely formated way then I would have been just building the strings that I
send to the `from_string` methods of the classes that need the data. Or I could
have made a million setters to set all the data, but that would have been a
nightmeare. I opted for making the user input data via the programs arguments.
I find that I hate programs which make you put anything into stdin and I end up
just piping input to them to might as well make it more scriptable right.
    Heres an outline of how and why classes got derived from each other.

Key: <- or ^- signifies that what is on the right is the base class of the left
     -> or \> signifies that what is on the left has whatever is on the right

uber::rides <- maxheap <- bst -> bst_node
    Rides manages all of the rides that the user creates. It handles loading
them from and saving them to files. maxheap and bst are templated so rides is a
maxheap of uber::ride. The rides are stored in the heap by a timestamp
therefore a maxheap keeps the one created most recently at the root, as
requested.

uber::ride <- uber::car <- transport::car
                        ^- circle
            ^- transport::ride <- transport::trip -> info::location <- info::address
            ^- info::customer <- info::contact
                                ^- info::credit_card
    Ride is the culmination of all the data we need. A ride needs to have
information on where you are going, which is a trip. A trip has two locations,
a start and an end. A location is either a set of latitude and longitude points
or and address or both. An uber ride also needs the information of the person
riding in the car. That person is a customer who has a name and a phone
numeber, which is contact information, as well as having credit card
information. The ride takes place in a car which makes it a car. Really this
should have just been transport::car so that it doesnt gain the requirement of
being a circlular linked list but I realized that now and dont have time to go
test it.

uber::car <- transport::car
            ^- circle
    A an uber car has all the information of a regular car but it also need to
be stored in a circular linked list. Circle is a class which is a node in a
cricular linked list as well as being the whole list. If you have just one car
then you also have the whole list of cars, without the need to have another
data structure to keep track of all of them.

    I feel that I was able to significatly reduce the amount of wrapper
functions needed by having almost all "is a" relationships.
