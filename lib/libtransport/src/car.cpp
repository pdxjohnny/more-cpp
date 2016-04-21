#include "transport.h"

transport::car::car() : value_year(0), value_make(NULL), value_model(NULL), value_plate_number(NULL), value_vin(NULL) {}

transport::car::car(car & copy) : value_year(copy.value_year), value_make(NULL), value_model(NULL), value_plate_number(NULL), value_vin(NULL) {
    MACRO_STRCPY_IF_NOT_NULL(this->value_make, copy.value_make);
    MACRO_STRCPY_IF_NOT_NULL(this->value_model, copy.value_model);
    MACRO_STRCPY_IF_NOT_NULL(this->value_plate_number, copy.value_plate_number);
    MACRO_STRCPY_IF_NOT_NULL(this->value_vin, copy.value_vin);
}

transport::car::car(int value_year, const char * value_make, const char * value_model, const char * value_plate_number, const char * value_vin) : value_year(value_year), value_make(NULL), value_model(NULL), value_plate_number(NULL), value_vin(NULL) {
    MACRO_STRCPY_IF_NOT_NULL(this->value_make, value_make);
    MACRO_STRCPY_IF_NOT_NULL(this->value_model, value_model);
    MACRO_STRCPY_IF_NOT_NULL(this->value_plate_number, value_plate_number);
    MACRO_STRCPY_IF_NOT_NULL(this->value_vin, value_vin);
}

transport::car::~car() {
    clear();
}

void transport::car::clear() {
    value_year = 0;
    MACRO_DELETE_ARRAY_IF_NOT_NULL(value_make);
    MACRO_DELETE_ARRAY_IF_NOT_NULL(value_model);
    MACRO_DELETE_ARRAY_IF_NOT_NULL(value_plate_number);
    MACRO_DELETE_ARRAY_IF_NOT_NULL(value_vin);
}

int transport::car::car_string_length() {
    // To store the length of the joined data
    int data_size = 0;
    // We also need to find out how many characters the value_year will take up
    char * value_year_buffer = NULL;
    if (value_year != 0) {
        value_year_buffer = new char[20];
        sprintf(value_year_buffer, "%d", value_year);
    }
    // Loop through all our data and add it find its size and then add it to
    // the buffer
    char ** data[] = {&value_year_buffer, &value_make, &value_model, &value_plate_number, &value_vin, NULL};
    // Find the size of the joined data
    data_size = strings::join_length(data, TRANSPORT_CAR_DELIM, TRANSPORT_CAR_DONT_HAVE);
    // Get rid of the value_year buffer
    delete[] value_year_buffer;
    return data_size;
}

int transport::car::car_to_string(char * buffer, int buffer_size) {
    // If join fails
    int err;
    // We also need to find out how many characters the value_year will take up
    char * value_year_buffer = NULL;
    if (value_year != 0) {
        value_year_buffer = new char[MACRO_NUM_TO_STR];
        sprintf(value_year_buffer, "%d", value_year);
    }
    // Loop through all our data and add it find its size and then add it to
    // the buffer
    char ** data[] = {&value_year_buffer, &value_make, &value_model, &value_plate_number, &value_vin, NULL};
    // Join the data together
    err = strings::join(buffer, data, TRANSPORT_CAR_DELIM, TRANSPORT_CAR_DONT_HAVE, buffer_size);
    // Get rid of the value_year code as a string
    MACRO_DELETE_ARRAY_IF_NOT_NULL(value_year_buffer);
    // Success is determined by join
    return err;
}

int transport::car::car_from_string(const char * from) {
    int err;
    // Lets pick a maximum value for the string to parse. Just so that we
    // ensure no one will pass us an insanly long string so that they can take
    // up memory
    if (strnlen(from, TRANSPORT_CAR_MAX) >= TRANSPORT_CAR_MAX) {
        errno = E2BIG;
        return -1;
    }
    // Free anthing we have existing
    clear();
    // Allocate a temporay value_year buffer to scan that data in
    char * value_year_buffer = NULL;
    // Parse them in
    // Loop through all our data and add it to the buffer
    char ** data[] = {&value_year_buffer, &value_make, &value_model, &value_plate_number,
        &value_vin, NULL};
    err = strings::parse(data, from, TRANSPORT_CAR_DELIM);
    // Parse may run out of data before it can fill all members so check to
    // value_make sure that the value_year was filled before converting it
    if (value_year_buffer == NULL) {
        return err;
    }
    // Convert the value_year code from a string to an int
    value_year = strtol(value_year_buffer, NULL, 10);
    // No need for the value_year code buffer anymore
    delete[] value_year_buffer;
    // Check if value_year code parsing failed
    if (errno == EINVAL || errno == ERANGE) {
        return -1;
    }
    // Success is determined by parse
    return err;
}

// The seters and getters :-(
int transport::car::year() {
    return value_year;
}

char * transport::car::make() {
    return value_make;
}

char * transport::car::model() {
    return value_model;
}

char * transport::car::plate_number() {
    return value_plate_number;
}

char * transport::car::vin() {
    return value_vin;
}
