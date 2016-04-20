#include "transport.h"

transport::ride::ride() {}

transport::ride::ride(ride & copy) : transport::trip(copy) {}

transport::ride::~ride() {}

float transport::ride::cost() {
    return distance_in_miles() * time(speed()) * fare_per_minute * fare_per_mile;
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
    err = strings::join(buffer, data, TRANSPORT_CAR_DELIM, TRANSPORT_CAR_DONT_HAVE, buffer_length);
    // Success is determined by join
    return err;
}
