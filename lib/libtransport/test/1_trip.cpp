#include "transport.h"

int test_trip_distance_in_miles() {
    // Make the trip object
    transport::trip flight(-122.35, 44.35, -121.35, 43.35);
    // Calculate the distance
    MACRO_TEST_FLOAT_EQ(flight.distance_in_miles(), 85.189499);
    // All is well
    return EXIT_SUCCESS;
}

int test_trip_distance_in_miles_fail() {
    // Make the trip object
    transport::trip flight;
    // Calculate the distance
    MACRO_TEST_FLOAT_EQ(flight.distance_in_miles(), -1.0);
    // All is well
    return EXIT_SUCCESS;
}

