#include "transport.h"

transport::ride::ride() {}

transport::ride::ride(ride & copy) : transport::trip(copy) {}

transport::ride::~ride() {}

float transport::ride::cost() {
    return distance_in_miles() * time(speed()) * fare_per_minute * fare_per_mile;
}
