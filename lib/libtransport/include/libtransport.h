#include <libinfo.h>

#ifndef LIBTRANSPORT
#define LIBTRANSPORT


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
        ~car();
    private:
        // Information associated with a car
        int year;
        char * make;
        char * model;
        char * plate_number;
        char * vin;
};

// A trip is travel between locations
class transport::trip {
    public:
        // Constuctors and destructors
        trip();
        ~trip();
        // Calculate the distance between start and end points
        float distance();
        // Calculate the time it would take to make this trip
        float time();
    private:
        // The average speed at which we can travel for this trip
        float speed;
        // The start and end locations of this trip
        info::location start;
        info::location end;
};

// A ride is a trip that costs money
class transport::ride : public trip {
    public:
        // Constuctors and destructors
        ride();
        ~ride();
        // Calculate the cost of the ride based on the distance and estimated
        // time of the trip
        float cost();
    private:
        // The least a ride can cost for it to be accepted by the driver
        float fare_minimum;
        // Base fare is like the drivers booking fee, it gets added on to the
        // cost of the trip
        float fare_base;
        // The cost per minute of the ride
        float fare_per_minute;
        // The cost per mile of the ride
        float fare_per_mile;
        // Fee associated with booking
        float fee_booking;
        // Fee associated with canclation
        float fee_cancel;
};

#endif

