#include "uber.h"

uber::ride::ride() {
    timestamp = std::time(NULL);
}

uber::ride::ride(uber::car & car, transport::ride & ride, info::customer & customer) : uber::car(car), transport::ride(ride), info::customer(customer) {
    timestamp = std::time(NULL);
}

uber::ride::~ride() {}

uber::ride & uber::ride::operator=(const uber::ride & copy) {
    uber::car::operator=(copy);
    transport::ride::operator=(copy);
    info::customer::operator=(copy);
    this->timestamp = copy.timestamp;
    return *this;
}

int uber::ride::ride_to_string_readable(char * buffer, int buffer_length) {
    const int str_length = 1000;
    // The ride
    char str_ride[str_length];
    transport::ride::ride_to_string_readable(str_ride, str_length);
    // The car we are riding in
    char str_car[str_length];
    car_to_string(str_car, str_length);
    // Format the output
    sprintf(buffer, "Ride requested at %s\n"
        "%s"
        "The car for this ride is a %s.\n",
        ctime(&this->timestamp),
        str_ride,
        str_car
    );
    return EXIT_SUCCESS;
}

int uber::ride::ride_to_string(char * buffer, int buffer_length) {
    // If join fails
    int err;
    // The start and end of the location
    const int str_length = 1000;
    // Ride information
    char str_ride[str_length];
    transport::ride::ride_to_string(str_ride, str_length);
    char * ptr_str_ride = str_ride;
    // Car information
    char str_car[str_length];
    car_to_string(str_car, str_length);
    char * ptr_str_car = str_car;
    // Time requested information
    char str_timestamp[MACRO_NUM_TO_STR];
    sprintf(str_timestamp, "%ld", timestamp);
    char * ptr_str_timestamp = str_timestamp;
    // The data we want to join
    char ** data[] = {&ptr_str_ride, &ptr_str_car, &ptr_str_timestamp, NULL};
    // Join the data together
    err = strings::join(buffer, data, TRANSPORT_RIDE_DELIM, TRANSPORT_RIDE_DONT_HAVE, buffer_length);
    // Success is determined by join
    return err;
}

int uber::ride::ride_from_string(const char * from) {
    int err;
    // Lets pick a maximum value for the string to parse. Just so that we
    // ensure no one will pass us an insanly long string so that they can take
    // up memory
    if (strnlen(from, TRANSPORT_RIDE_MAX) >= TRANSPORT_RIDE_MAX) {
        return -1;
    }
    // Pointers that will hold parsed in strings
    char * str_ride = NULL;
    char * str_cost = NULL;
    char * str_car = NULL;
    char * str_timestamp = NULL;
    // Parse them in
    // Loop through all our data and add it to the buffer
    char ** data[] = {&str_ride, &str_cost, &str_car, &str_timestamp, NULL};
    err = strings::parse(data, from, TRANSPORT_RIDE_DELIM);
    // Make sure parsing worked
    if (err != EXIT_SUCCESS) {
        goto DELETE_AND_EXIT;
    }
    // Parse in the ride data
    err = transport::ride::ride_from_string(str_ride);
    if (err != EXIT_SUCCESS) {
        goto DELETE_AND_EXIT;
    }
    // Parse in the car data
    err = car_from_string(str_car);
    if (err != EXIT_SUCCESS) {
        goto DELETE_AND_EXIT;
    }
    // Parse in the timestamp data
    errno = EXIT_SUCCESS;
    this->timestamp = strtol(str_timestamp, NULL, 10);
    // Check if parsing failed
    if (errno == ERANGE) {
        err = -1;
        goto DELETE_AND_EXIT;
    }
DELETE_AND_EXIT:
    MACRO_DELETE_ARRAY_IF_NOT_NULL(str_ride);
    MACRO_DELETE_ARRAY_IF_NOT_NULL(str_cost);
    MACRO_DELETE_ARRAY_IF_NOT_NULL(str_car);
    MACRO_DELETE_ARRAY_IF_NOT_NULL(str_timestamp);
    // Success is determined by parse
    return err;
}

time_t uber::ride::time_requested() {
    return this->timestamp;
}
