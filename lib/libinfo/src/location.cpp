#include "info.h"
#include <libinfo.h>

info::location::location() : lng(0.0), lat(0.0) {}

info::location::location(double lng, double lat) : lng(lng), lat(lat) {}

info::location::~location() {}

int info::location::address_from_string(const char * from) {
    // Populate the address data
    info::address::address_from_string(from);
    // We no longer know the latitude and longitude of our location so clear it
    lng = 0.0;
    lat = 0.0;
    return EXIT_SUCCESS;
}

int info::location::lnglat(double * lng, double * lat) {
    if (lng != NULL) {
        *lng = this->lng;
    }
    if (lat != NULL) {
        *lat = this->lat;
    }
    return EXIT_SUCCESS;
}

int info::location::lnglat(double lng, double lat) {
    // We no longer know the latitude and longitude of our location so clear it
    this->lng = lng;
    this->lat = lat;
    // Clear the address data
    info::address::address_from_string("");
    return EXIT_SUCCESS;
}

