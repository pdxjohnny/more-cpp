
                                DESIGN DOC UBER CLONE
                                    John Andersen
                                      04/07/2016

    This program is a ride for hire service with a tiered approch to ride
quality. There are three tiers, standard, premium, and group. Each tier has
different attributes and citeria that defines it. To create this program in an
object oriented fashon we need to specify all the aspects of how a ride for
hire service operates and what information it needs to operate.
    A ride sharing system is made up of three categories. The first category is
information. Information is any data which does not need the rest of the ride
for hire program to be of value. It could be used in many applications. The
information classes that I will be creating include address, location, payment,
person and customer. An address is made up of a building number and street, zip
code, country, and state or province. An address could be something that a
person, customer, payment, or location has. A location could be an address. For
the purposes of this program we no not need address information for a person,
customer, or payment, however that may be nessicary for another problem. I have
decided to make it so a location is an address. The location could have also
had an address be either way there will be wrapper functions around the
population of the address feilds and the display of the address. This is
because a location could be an address or it could be a set of longitude and
latitude cordinates. A location should be able to calculate its distance from
another location and report its latitude and longitude or address depending on
if it has one the other or both. A location might also need to find the address
it is at if it only has latitude and longitude data. Inversly is may need to
find the latitude and longitude it is at if it only has the address. For these
reasons it is nessicary to put a wrapper around our base class of addresses
functions which display and parse an address so that when we receive new
address data we clear the latitude and longitude data, and vise versa.
    A person will be a class with holds someones name for now. In the future it
may hold other data but as of now that is all we need it to do. A customer is a
person but has information on their phone number and email address etc. Payment
information is data on a customer plus the information about their credit card
and so forth. Those are the types of information that are needed in this
program but are also applicable elsewhere.
    Now we move into the slightly more application specific classes. This is an
application where dirvers of private cars will be taking people on trips and
expect to be payed for their services. In addition we also have different
levels of service. The classes that need to be created relating to the
transportation aspect of the program are a car, trip, ride, and the different
variations or rides for our three tiers. A car holds information such as the
make, model, year, licence plate number, and vin. A trip is set of locations
from start to end which we travel an average speed during. Trips should be able
to calculate the time they will take as well as the distance that will be
traveled. A ride is a trip where someone is driving someone else expecting to
be paid. A ride does not nessicarily have to be a car though, one could ride on
a boat or a plane. A ride is a trip which can calculate the cost of the trip.
    We are now to the application specific code. What I mean by this is that I
dont invision this code being reused for say a banking application, where as
some of the other classes may have still applied. Now we need to create the
three ride options, standard, premium, and group. These ride options are a ride
and they are driving by car. Therefore standard, premium, and group are all
rides and cars, derived from both. As such when they are intanciated they will
have different values of fares as well as different acceptable values of make,
model, and year. If you order a peimium ride and a standard car applies to give
you that ride the ride should deny them the oppertunity to give you that ride.
The logic for which cars are acceptable is unique to each class and therefore
makes sense to make them all unique at this point. The only exact similarity
between them is that they all have customer info. Calculating payment is all
done differently though so that only means two lines of similar code, where the
payment information is defined in the class and when the call is made to
withdraw from that payment information.
    Getting even more specific we now need to manage all of the rides which are
being requested. To do this we will have circular linked lists of each tier of
rides. I want to try what Karla said about making the node itself the same as
the list that sounds like a clever approch. There will also be a balenced tree
used for storing all the appointments that have been made. This will be a red
black tree and it will be templated so that I can reuse it for the next n
assingments.

Thanks,
John

