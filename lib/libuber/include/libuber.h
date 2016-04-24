/*
 * John Andersen
 * File: libuber/include/libuber.h
*/

#include <ctime>

#include <libbst.h>
#include <libmaxheap.h>
#include <libcircle.h>
#include <libtransport.h>

// Return values of class chooser
#define UBER_CAR_STANDARD 1
#define UBER_CAR_PREMIUM 2
#define UBER_CAR_GROUP 3

#define UBER_RIDE_DELIM " | "
#define UBER_RIDE_DONT_HAVE "unavailable"
#define UBER_RIDE_MAX 1000

namespace uber {
    // Functions
    // Tells us was uber car this car should be, so we know how to configure it
    char car_type(transport::car &);
    char is_premium(transport::car &);
    char is_group(transport::car &);
    // Classes
    class car;
    class ride;
    class rides;
};

// Our cars need to be a list and a car so we can have lists of them
class uber::car : public circle, public transport::car {
public:
    car();
    car(car &);
    car(int year, const char * make, const char * model, const char * plate_number, const char * vin);
    car & operator=(const uber::car & copy);
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
class uber::ride : public uber::car, public transport::ride, public info::customer {
public:
    ride();
    ride(ride &);
    ~ride();
    ride(uber::car &, transport::ride &, info::customer &);
    ride & operator=(const uber::ride & copy);
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
// class uber::rides : public bst<uber::ride> {
class uber::rides : public maxheap<uber::ride> {
public:
    rides();
    ~rides();
    int load(int fd);
    int save(int fd);
    int print();
};
