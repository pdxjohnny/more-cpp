/*
 * John Andersen
 * File: libtransport/src/trip.cpp
*/

#include "transport.h"

transport::trip::trip() {}

transport::trip::trip(info::location & start, info::location & end) : start(start), end(end) {}

transport::trip::trip(trip & copy) : start(copy.start), end(copy.end) {}

transport::trip::trip(double start_lng, double start_lat, double end_lng, double end_lat) : start(start_lng, start_lat), end(end_lng, end_lat) {}

transport::trip::~trip() {}

transport::trip & transport::trip::operator=(const transport::trip & copy) {
    this->start = copy.start;
    this->end = copy.end;
    return *this;
}

float transport::trip::distance_in_miles() {
    return start.distance_in_miles(end);
}

float transport::trip::time(float speed) {
    return distance_in_miles() / speed * MACRO_HOURS_TO_MINUTES;
}

float transport::trip::speed() {
    // TODO ask google how long it will take
    return 20;
}

int transport::trip::trip_to_string_readable(char * buffer, int buffer_length) {
    const int str_length = 500;
    char start_str[str_length];
    char end_str[str_length];
    start.location_to_string(start_str, str_length);
    end.location_to_string(end_str, str_length);
    sprintf(buffer, "Traveling at %02f mph "
        "over a distance of %02f miles "
        "will take %02f minutes.\n"
        "Starting at %s.\n"
        "Ending at %s.\n",
        speed(),
        distance_in_miles(),
        time(speed()),
        start_str,
        end_str
    );
    return EXIT_SUCCESS;
}

int transport::trip::trip_to_string(char * buffer, int buffer_length) {
    // If join fails
    int err;
    // The start and end of the location
    const int str_length = 500;
    // Start location
    char start_str[str_length];
    start.location_to_string(start_str, str_length);
    char * start_str_ptr = start_str;
    // End location
    char end_str[str_length];
    end.location_to_string(end_str, str_length);
    char * end_str_ptr = end_str;
    // Speed
    char speed_str[MACRO_NUM_TO_STR];
    sprintf(speed_str, "%f", speed());
    char * speed_str_ptr = speed_str;
    // Distance in miles
    char distance_in_miles_str[MACRO_NUM_TO_STR];
    sprintf(distance_in_miles_str, "%f", distance_in_miles());
    char * distance_in_miles_str_ptr = distance_in_miles_str;
    // Time
    char time_str[MACRO_NUM_TO_STR];
    sprintf(time_str, "%f", time(speed()));
    char * time_str_ptr = time_str;
    // The data we want to join
    char ** data[] = {&start_str_ptr, &end_str_ptr, &speed_str_ptr,
        &distance_in_miles_str_ptr, &time_str_ptr, NULL};
    // Join the data together
    err = strings::join(buffer, data, TRANSPORT_TRIP_DELIM, TRANSPORT_TRIP_DONT_HAVE, buffer_length);
    // Success is determined by join
    return err;
}

int transport::trip::trip_from_string(const char * from) {
    int err;
    // Lets pick a maximum value for the string to parse. Just so that we
    // ensure no one will pass us an insanly long string so that they can take
    // up memory
    if (strnlen(from, TRANSPORT_TRIP_MAX) >= TRANSPORT_TRIP_MAX) {
        return -1;
    }
    // Pointers that will hold parsed in strings
    char * str_start = NULL;
    char * str_end = NULL;
    // Parse them in
    // Loop through all our data and add it to the buffer
    char ** data[] = {&str_start, &str_end, NULL};
    err = strings::parse(data, from, TRANSPORT_TRIP_DELIM);
    if (err != EXIT_SUCCESS) {
        return err;
    }
    // Convert and parse in
    start.location_from_string(str_start);
    end.location_from_string(str_end);
    // Delete the memory given to us by parse
    MACRO_DELETE_ARRAY_IF_NOT_NULL(str_start);
    MACRO_DELETE_ARRAY_IF_NOT_NULL(str_end);
    // Check if parsing failed
    if (errno == ERANGE) {
        return -1;
    }
    // Success is determined by parse
    return err;
}
