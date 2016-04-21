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

int test_trip_trip_to_string() {
    // Create the locations we want
    info::location start(-122.35, 44.35);
    start.update_address_from_string("2000 NE Glisan Street, Portland, OR, 97268, USA");
    info::location end(-121.35, 43.35);
    end.update_address_from_string("1000 SW Salmon Street, Portland, OR, 97225, USA");
    // Make the trip object
    transport::trip trip(start, end);
    // Make the string to put the formated trip in
    char trip_string[400];
    // Put the trip transportrmation in that string
    MACRO_TEST_EQ(trip.trip_to_string(trip_string, 400), 0);
    // Make sure the transportrmation put in was correct
    char check[] = "2000 NE Glisan Street, Portland, OR, 97268"
        ", USA . 44.350000 . -122.350000 - "
        "1000 SW Salmon Street, Portland, OR, 97225"
        ", USA . 43.350000 . -121.350000"
        " - 20.000000 - 85.189499 - 255.568481";
    MACRO_TEST_MEM_STR_EQ(trip_string, check);
    return EXIT_SUCCESS;
}

int test_trip_trip_from_string() {
    // Make it parse this and if it comes out the same were good
    char input[] = "2000 NE Glisan Street, Portland, OR, 97268"
        ", USA . 44.350000 . -122.350000 - "
        "1000 SW Salmon Street, Portland, OR, 97225"
        ", USA . 43.350000 . -121.350000"
        " - 20.000000 - 85.189499 - 255.568481";
    // output is slightly different because of floats
    char output[] = "2000 NE Glisan Street, Portland, OR, 97268"
        ", USA . 44.349998 . -122.349998 - "
        "1000 SW Salmon Street, Portland, OR, 97225"
        ", USA . 43.349998 . -121.349998"
        " - 20.000000 - 85.189499 - 255.568481";
    // Make the trip object
    transport::trip trip;
    // Make the string to put the formated trip in
    char trip_string[400];
    // Parse it in
    MACRO_TEST_EQ(trip.trip_from_string(input), 0);
    // Put the trip into a string to check against
    MACRO_TEST_EQ(trip.trip_to_string(trip_string, 400), 0);
    // Check it
    MACRO_TEST_MEM_STR_EQ(trip_string, output);
    return EXIT_SUCCESS;
}
