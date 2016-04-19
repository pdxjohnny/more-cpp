#include "transport.h"

transport::trip::trip() {}

transport::trip::trip(trip & copy) : start(copy.start), end(copy.end) {}

transport::trip::trip(double start_lng, double start_lat, double end_lng, double end_lat) : start(start_lng, start_lat), end(end_lng, end_lat) {}

transport::trip::~trip() {}

float transport::trip::distance_in_miles() {
    return start.distance_in_miles(end);
}

float transport::trip::time(float speed) {
    return distance_in_miles() * speed;
}

float transport::trip::speed() {
    // TODO ask google how long it will take
    return 20;
}
