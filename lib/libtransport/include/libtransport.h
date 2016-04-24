#include <libinfo.h>

#ifndef LIBTRANSPORT
#define LIBTRANSPORT

#define TRANSPORT_CAR_DELIM ", "
#define TRANSPORT_CAR_DONT_HAVE "unavailable"
#define TRANSPORT_CAR_MAX 200

#define TRANSPORT_TRIP_DELIM " - "
#define TRANSPORT_TRIP_DONT_HAVE "unavailable"
#define TRANSPORT_TRIP_MAX 300

#define TRANSPORT_RIDE_DELIM " / "
#define TRANSPORT_RIDE_DONT_HAVE "unavailable"
#define TRANSPORT_RIDE_MAX 600

namespace transport {
    // Test functions sould return 42
    int test();
    // Classes that are transport related
    class car;
    class trip;
    class ride;
};

// A car is a mode of transport
class transport::car {
    public:
        // Constuctors and destructors
        car();
        car(car &);
        // If you wish to initiallize with members set this is your constuctor
        car(int, const char *, const char *, const char *, const char *);
        car & operator=(const transport::car & copy);
        virtual ~car();
        // Erases any daat we are holding
        void clear();
        // The length of what the car formated as a string will be
        int car_string_length();
        // Formats itself as a string
        // Returns -1 if it failed
        int car_to_string(char * buffer, int buffer_size);
        // Parses an car from a NULL terminated string
        // Returns -1 if all fields could not be found
        int car_from_string(const char *);
        // Well what else am I supposed to do I dont see a way around this
        int year();
        char * make();
        char * model();
        char * plate_number();
        char * vin();
    private:
        // Information associated with a car
        int value_year;
        char * value_make;
        char * value_model;
        char * value_plate_number;
        char * value_vin;
};

// A trip is travel between locations
class transport::trip {
    public:
        // Constuctors and destructors
        trip();
        trip(trip &);
        trip(info::location & start, info::location & end);
        trip(double start_lng, double start_lat, double end_lng, double end_lat);
        trip & operator=(const transport::trip & copy);
        virtual ~trip();
        // Calculate the distance between start and end points
        float distance_in_miles();
        // Calculate the time it would take to make this trip
        // The average speed at which we can travel for this trip
        virtual float time(float speed);
        // Calculate the average speed (in mph) based on traffic and such
        float speed();
        // Output the trip
        int trip_to_string_readable(char * buffer, int buffer_length);
        int trip_to_string(char * buffer, int buffer_length);
        // Parse from a string
        int trip_from_string(const char *);
    private:
        // The start and end locations of this trip
        info::location start;
        info::location end;
};

// A ride is a trip that costs money
class transport::ride : public transport::trip {
    public:
        // Constuctors and destructors
        ride();
        // Initailize with all of fares
        ride(float, float, float, float, info::location &, info::location &);
        ride(ride &);
        ride & operator=(const transport::ride & copy);
        virtual ~ride();
        // Calculate the cost of the ride based on the distance and estimated
        // time of the trip
        virtual float cost();
        // Output the ride
        int ride_to_string_readable(char * buffer, int buffer_length);
        int ride_to_string(char * buffer, int buffer_length);
        // Parse from a string
        int ride_from_string(const char *);
    private:
        // The least a ride can cost for it to be accepted by the driver
        float fare_minimum;
        // The cost per mile of the ride
        float fare_per_mile;
        // Fee associated with booking
        float fee_booking;
        // Fee associated with canclation
        float fee_cancel;
};

#endif

