#include "transport.h"

transport::car::car() : year(0), make(NULL), model(NULL), plate_number(NULL), vin(NULL) {}

transport::car::car(int year, const char * make, const char * model, const char * plate_number, const char * vin) : year(year), make(NULL), model(NULL), plate_number(NULL), vin(NULL) {
    MACRO_STRCPY_IF_NOT_NULL(this->make, make);
    MACRO_STRCPY_IF_NOT_NULL(this->model, model);
    MACRO_STRCPY_IF_NOT_NULL(this->plate_number, plate_number);
    MACRO_STRCPY_IF_NOT_NULL(this->vin, vin);
}

transport::car::~car() {
    clear();
}

void transport::car::clear() {
    year = 0;
    MACRO_DELETE_ARRAY_IF_NOT_NULL(make);
    MACRO_DELETE_ARRAY_IF_NOT_NULL(model);
    MACRO_DELETE_ARRAY_IF_NOT_NULL(plate_number);
    MACRO_DELETE_ARRAY_IF_NOT_NULL(vin);
}

int transport::car::car_string_length() {
    // To store the length of the joined data
    int data_size = 0;
    // We also need to find out how many characters the year will take up
    char * year_buffer = NULL;
    if (year != 0) {
        year_buffer = new char[20];
        sprintf(year_buffer, "%d", year);
    }
    // Loop through all our data and add it find its size and then add it to
    // the buffer
    char ** data[] = {&make, &model, &plate_number, &year_buffer, &vin, NULL};
    // Find the size of the joined data
    data_size = strings::join_length(data, TRANSPORT_CAR_DELIM, TRANSPORT_CAR_DONT_HAVE);
    // Get rid of the year buffer
    delete[] year_buffer;
    return data_size;
}

int transport::car::car_to_string(char * buffer, int buffer_size) {
    // If join fails
    int err;
    // If we dont have data on something report n/a
    char dont_have[] = TRANSPORT_CAR_DONT_HAVE;
    // We also need to find out how many characters the year will take up
    char * year_buffer = NULL;
    if (year != 0) {
        year_buffer = new char[20];
        sprintf(year_buffer, "%d", year);
    }
    // Loop through all our data and add it find its size and then add it to
    // the buffer
    char ** data[] = {&make, &model, &plate_number, &year_buffer, &vin, NULL};
    // Join the data together
    err = strings::join(buffer, data, TRANSPORT_CAR_DELIM, TRANSPORT_CAR_DONT_HAVE, buffer_size);
    // Get rid of the year code as a string
    delete[] year_buffer;
    // Success is determined by join
    return err;
}

int transport::car::car_from_string(const char * from) {
    int err;
    // Lets pick a maximum value for the string to parse. Just so that we
    // ensure no one will pass us an insanly long string so that they can take
    // up memory
    if (strnlen(from, TRANSPORT_CAR_MAX) >= TRANSPORT_CAR_MAX) {
        return -1;
    }
    // Allocate a temporay year buffer to scan that data in
    char * year_buffer = NULL;
    // Parse them in
    // Loop through all our data and add it to the buffer
    char ** data[] = {&make, &model, &plate_number, &year_buffer,
        &vin, NULL};
    err = strings::parse(data, from, TRANSPORT_CAR_DELIM);
    // Parse may run out of data before it can fill all members so check to
    // make sure that the year was filled before converting it
    if (year_buffer == NULL) {
        return err;
    }
    // Convert the year code from a string to an int
    year = strtol(year_buffer, NULL, 10);
    // No need for the year code buffer anymore
    delete[] year_buffer;
    // Check if year code parsing failed
    if (errno == EINVAL || errno == ERANGE) {
        return -1;
    }
    // Success is determined by parse
    return err;
}

