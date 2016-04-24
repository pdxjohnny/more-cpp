/*
 * John Andersen
 * File: libcards/include/libcards.h
*/

#include <ctime>

#include <libbst.h>
#include <libmaxheap.h>
#include <libcircle.h>
#include <libtransport.h>

// Return values of class chooser
#define CARDS_CAR_STANDARD 1
#define CARDS_CAR_PREMIUM 2
#define CARDS_CAR_GROUP 3

#define CARDS_RIDE_DELIM " | "
#define CARDS_RIDE_DONT_HAVE "unavailable"
#define CARDS_RIDE_MAX 1000

namespace cards {
    // Functions
    // Tells us was cards car this car should be, so we know how to configure it
    char car_type(transport::car &);
    char is_premium(transport::car &);
    char is_group(transport::car &);
    // Classes
    class car;
    class ride;
    class rides;
};

// Our cars need to be a list and a car so we can have lists of them
class cards::car : public circle, public transport::car {
public:
    car();
    car(car &);
    car(int year, const char * make, const char * model, const char * plate_number, const char * vin);
    car & operator=(const cards::car & copy);
    virtual char match(circle * node);
    virtual char sort(circle * node);
    char *** unique_makes_models ();
    int save(int fd);
    int print();
private:
    class oneach_unique_makes_models;
    class oneach_save;
    class oneach_print;
};

// A ride is what happens when a customer accepts a car
class cards::ride : public cards::car, public transport::ride, public info::customer {
public:
    ride();
    ride(ride &);
    ~ride();
    ride(cards::car &, transport::ride &, info::customer &);
    ride & operator=(const cards::ride & copy);
    // The ride formated as a string
    int ride_to_string_readable(char * buffer, int buffer_length);
    int ride_to_string(char * buffer, int buffer_length);
    // Parse from a string
    int ride_from_string(const char *);
    // The time that this ride was requested
    time_t time_requested();
private:
    time_t timestamp;
};

// Manages all the rides in a maxheap
// class cards::rides : public bst<cards::ride> {
class cards::rides : public maxheap<cards::ride> {
public:
    rides();
    ~rides();
    int load(int fd);
    int save(int fd);
    int print();
};
