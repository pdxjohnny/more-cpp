#include <libcircle.h>
#include <libtransport.h>

namespace uber {
    class car;
    class ride;
};

// Our cars need to be a list and a car so we can have lists of them
class uber::car : public circle, public transport::car {
public:
    car(car &);
    car(int year, const char * make, const char * model, const char * plate_number, const char * vin);
    virtual char match(circle * node);
    virtual char sort(circle * node);
    char *** unique_makes_models ();
private:
    class oneach_unique_makes_models;
};

// A ride is what happens when a customer accepts a car
class uber::ride : public uber::car, public transport::ride {
public:
    ride(uber::car &, transport::ride &);
    // Ride information as a string, remeber to free the array it returns
    char * ride_to_string();
};

