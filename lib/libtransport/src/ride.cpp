#include "transport.h"

transport::ride::ride() : fare_minimum(0), fare_base(0), fare_per_minute(1), fare_per_mile(1), fee_booking(0), fee_cancel(0) {}

transport::ride::ride(ride & copy) : transport::trip(copy), fare_minimum(0), fare_base(0), fare_per_minute(1), fare_per_mile(1), fee_booking(0), fee_cancel(0) {}

transport::ride::~ride() {}

float transport::ride::cost() {
    return (time(speed()) * fare_per_minute) + (distance_in_miles() * fare_per_mile);
}

int transport::ride::ride_to_string_readable(char * buffer, int buffer_length) {
    const int str_length = 500;
    char trip_str[str_length];
    trip_to_string_readable(trip_str, str_length);
    sprintf(buffer, "%s"
        "Total cost is $%02f.\n",
        trip_str,
        cost()
    );
    return EXIT_SUCCESS;
}

int transport::ride::ride_to_string(char * buffer, int buffer_length) {
    // If join fails
    int err;
    // The start and end of the location
    const int str_length = 1000;
    // Trip information
    char trip_str[str_length];
    trip_to_string(trip_str, str_length);
    char * trip_str_ptr = trip_str;
    // Cost
    char cost_str[MACRO_NUM_TO_STR];
    sprintf(cost_str, "%f", cost());
    char * cost_str_ptr = cost_str;
    // The data we want to join
    char ** data[] = {&trip_str_ptr, &cost_str_ptr, NULL};
    // Join the data together
    err = strings::join(buffer, data, TRANSPORT_RIDE_DELIM, TRANSPORT_RIDE_DONT_HAVE, buffer_length);
    // Success is determined by join
    return err;
}

int transport::ride::ride_from_string(const char * from) {
    int err;
    // Lets pick a maximum value for the string to parse. Just so that we
    // ensure no one will pass us an insanly long string so that they can take
    // up memory
    if (strnlen(from, TRANSPORT_RIDE_MAX) >= TRANSPORT_RIDE_MAX) {
        return -1;
    }
    // Pointers that will hold parsed in strings
    char * str_trip = NULL;
    // Parse them in
    // Loop through all our data and add it to the buffer
    char ** data[] = {&str_trip, NULL};
    err = strings::parse(data, from, TRANSPORT_RIDE_DELIM);
    if (err != EXIT_SUCCESS) {
        return err;
    }
    // Convert and parse in
    trip_from_string(str_trip);
    // Delete the memory given to us by parse
    MACRO_DELETE_ARRAY_IF_NOT_NULL(str_trip);
    // Check if parsing failed
    if (errno == ERANGE) {
        return -1;
    }
    // Success is determined by parse
    return err;
}
