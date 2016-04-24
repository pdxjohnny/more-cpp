#include "transport.h"

transport::ride::ride() : fare_minimum(0), fare_per_mile(1), fee_booking(0), fee_cancel(0) {}

transport::ride::ride(
        float fare_minimum, float fare_per_mile,
        float fee_booking, float fee_cancel,
        info::location & start, info::location & end
    ) :
    transport::trip(start, end),
    fare_minimum(fare_minimum), fare_per_mile(fare_per_mile),
    fee_booking(fee_booking), fee_cancel(fee_cancel)
    {
}

transport::ride::ride(ride & copy) : transport::trip(copy), fare_minimum(copy.fare_minimum), fare_per_mile(copy.fare_per_mile), fee_booking(copy.fee_booking), fee_cancel(copy.fee_cancel) {}

transport::ride::~ride() {}

transport::ride & transport::ride::operator=(const transport::ride & copy) {
    transport::trip::operator=(copy);
    this->fare_minimum = copy.fare_minimum;
    this->fare_per_mile = copy.fare_per_mile;
    this->fee_booking = copy.fee_booking;
    this->fee_cancel = copy.fee_cancel;
    return *this;
}

float transport::ride::cost() {
    return fee_booking + fare_minimum + (distance_in_miles() * fare_per_mile);
}

int transport::ride::ride_to_string_readable(char * buffer, int buffer_length) {
    const int str_length = 500;
    char trip_str[str_length];
    trip_to_string_readable(trip_str, str_length);
    sprintf(buffer, "%s"
        "Total cost is $%0.02f.\n"
        "Booking fee $%0.02f, Cancelation fee $%0.02f, Fare per mile $%0.02f, Comfort fee $%0.02f",
        trip_str,
        cost(),
        fee_booking, fee_cancel, fare_per_mile, fare_minimum
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
    // fare_minimum
    char fare_minimum_str[MACRO_NUM_TO_STR];
    sprintf(fare_minimum_str, "%0.02f", fare_minimum);
    char * fare_minimum_str_ptr = fare_minimum_str;
    // fare_per_mile
    char fare_per_mile_str[MACRO_NUM_TO_STR];
    sprintf(fare_per_mile_str, "%0.02f", fare_per_mile);
    char * fare_per_mile_str_ptr = fare_per_mile_str;
    // fee_booking
    char fee_booking_str[MACRO_NUM_TO_STR];
    sprintf(fee_booking_str, "%0.02f", fee_booking);
    char * fee_booking_str_ptr = fee_booking_str;
    // fee_cancel
    char fee_cancel_str[MACRO_NUM_TO_STR];
    sprintf(fee_cancel_str, "%0.02f", fee_cancel);
    char * fee_cancel_str_ptr = fee_cancel_str;
    // The data we want to join
    char ** data[] = {&trip_str_ptr, &fare_minimum_str_ptr,
        &fare_per_mile_str_ptr, &fee_booking_str_ptr, &fee_cancel_str_ptr, NULL};
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
        errno = E2BIG;
        return -1;
    }
    // Pointers that will hold parsed in strings
    char * str_trip = NULL;
    char * str_fare_minimum = NULL;
    char * str_fare_per_mile = NULL;
    char * str_fee_booking = NULL;
    char * str_fee_cancel = NULL;
    // Parse them in
    // Loop through all our data and add it to the buffer
    char ** data[] = {&str_trip, &str_fare_minimum,
        &str_fare_per_mile, &str_fee_booking, &str_fee_cancel, NULL};
    err = strings::parse(data, from, TRANSPORT_RIDE_DELIM);
    // Make sure parsing worked
    if (err != EXIT_SUCCESS) {
        goto DELETE_AND_EXIT;
    }
    // Parse in the trip data
    err = trip_from_string(str_trip);
    if (err != EXIT_SUCCESS) {
        goto DELETE_AND_EXIT;
    }
    // Parse in the fare and fee data
    errno = EXIT_SUCCESS;
    this->fare_minimum = strtof(str_fare_minimum, NULL);
    // Check if parsing failed
    if (errno == ERANGE) {
        err = -1;
        goto DELETE_AND_EXIT;
    }
    errno = EXIT_SUCCESS;
    this->fare_per_mile = strtof(str_fare_per_mile, NULL);
    // Check if parsing failed
    if (errno == ERANGE) {
        err = -1;
        goto DELETE_AND_EXIT;
    }
    errno = EXIT_SUCCESS;
    this->fee_booking = strtof(str_fee_booking, NULL);
    // Check if parsing failed
    if (errno == ERANGE) {
        err = -1;
        goto DELETE_AND_EXIT;
    }
    errno = EXIT_SUCCESS;
    this->fee_cancel = strtof(str_fee_cancel, NULL);
    // Check if parsing failed
    if (errno == ERANGE) {
        err = -1;
        goto DELETE_AND_EXIT;
    }
DELETE_AND_EXIT:
    MACRO_DELETE_ARRAY_IF_NOT_NULL(str_trip);
    MACRO_DELETE_ARRAY_IF_NOT_NULL(str_fare_minimum);
    MACRO_DELETE_ARRAY_IF_NOT_NULL(str_fare_per_mile);
    MACRO_DELETE_ARRAY_IF_NOT_NULL(str_fee_booking);
    MACRO_DELETE_ARRAY_IF_NOT_NULL(str_fee_cancel);
    // Success is determined by parse
    return err;
}
