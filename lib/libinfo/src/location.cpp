#include "info.h"
#include <libinfo.h>

info::location::location() : lng(0.0), lat(0.0) {}

info::location::location(location & copy) : info::address(copy), lng(copy.lng), lat(copy.lat) {}

info::location::location(double lng, double lat) : lng(lng), lat(lat) {}

info::location::location(int zip, const char * street, const char * city, const char * state_or_province, const char * country) : info::address(zip, street, city, state_or_province, country), lng(0.0), lat(0.0) {}

info::location::~location() {}

void info::location::clear () {
    // Clear the address
    info::address::clear();
    // Clear the lng lat
    lng = 0.0;
    lat = 0.0;
}

int info::location::address_from_string(const char * from) {
    int err;
    // Populate the address data
    err = update_address_from_string(from);
    // We no longer know the latitude and longitude of our location so clear it
    lng = 0.0;
    lat = 0.0;
    return err;
}

int info::location::update_address_from_string(const char * from) {
    // Populate the address data
    return info::address::address_from_string(from);
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
    // Set the new lng lat
    update_lnglat(lng, lat);
    // Clear the address data
    info::address::clear();
    return EXIT_SUCCESS;
}

int info::location::update_lnglat(double lng, double lat) {
    this->lng = lng;
    this->lat = lat;
    return EXIT_SUCCESS;
}

float info::location::distance_in_miles(const location & point) {
    /*
     * dlon = lon2 - lon1
     * dlat = lat2 - lat1
     * a = (sin(dlat/2))^2 + cos(lat1) * cos(lat2) * (sin(dlon/2))^2
     * c = 2 * atan2( sqrt(a), sqrt(1-a) )
     * d = R * c (where R is the radius of the Earth)
    */
    // Make sure the we have lng and lat and the opther point does too
    MACRO_CANT_EQ(lng, 0.0);
    MACRO_CANT_EQ(lat, 0.0);
    MACRO_CANT_EQ(point.lng, 0.0);
    MACRO_CANT_EQ(point.lat, 0.0);
    // Convert from degrees to radians
    double lat_r = lat * M_PI / 180.0;
    double plat_r = point.lat * M_PI / 180.0;
    double dlng = (lng - point.lng) * M_PI / 180.0;
    double dlat = (lat - point.lat) * M_PI / 180.0;
    // Preform the haversine formula
    double a = pow(sin(dlat / 2.0), 2.0) +
        (cos(lat_r) * cos(plat_r) *
        pow(sin(dlng / 2.0), 2.0));
    return INFO_EARTHS_RADIUS_IN_MILES * 2.0 * atan2(
        sqrt(a), sqrt(1.0 - a)
    );
}

int info::location::location_to_string(char * buffer, int buffer_size) {
    // If join fails
    int err;
    // We also need to find out how many characters the zip will take up
    const int address_length = address_string_length() + 1;
    char * address_buffer = new char [address_length];
    // Address as a string
    address_to_string(address_buffer, address_length);
    // The lat and lng as strings
    char lat_str[20];
    char lng_str[20];
    sprintf(lat_str, "%f", lat);
    sprintf(lng_str, "%f", lng);
    char * lat_str_ptr = lat_str;
    char * lng_str_ptr = lng_str;
    // The data we want to join
    char ** data[] = {&address_buffer, &lat_str_ptr, &lng_str_ptr, NULL};
    // Join the data together
    err = strings::join(buffer, data, INFO_LOCATION_DELIM, INFO_LOCATION_DONT_HAVE, buffer_size);
    // Free the buffers
    MACRO_DELETE_ARRAY_IF_NOT_NULL(address_buffer);
    // Success is determined by join
    return err;
}

int info::location::location_from_string(const char * from) {
    int err;
    // Lets pick a maximum value for the string to parse. Just so that we
    // ensure no one will pass us an insanly long string so that they can take
    // up memory
    if (strnlen(from, INFO_LOCATION_MAX) >= INFO_LOCATION_MAX) {
        errno = E2BIG;
        return -1;
    }
    // Pointers that will hold parsed in strings
    char * address_str = NULL;
    char * lat_str = NULL;
    char * lng_str = NULL;
    // Parse them in
    // Loop through all our data and add it to the buffer
    char ** data[] = {&address_str, &lat_str, &lng_str, NULL};
    err = strings::parse(data, from, INFO_LOCATION_DELIM);
    if (err != EXIT_SUCCESS) {
        MACRO_DELETE_ARRAY_IF_NOT_NULL(address_str);
        MACRO_DELETE_ARRAY_IF_NOT_NULL(lat_str);
        MACRO_DELETE_ARRAY_IF_NOT_NULL(lng_str);
        return err;
    }
    // Convert and parse in
    address_from_string(address_str);
    lat = strtof(lat_str, NULL);
    lng = strtof(lng_str, NULL);
    // Delete the memory given to us by parse
    MACRO_DELETE_ARRAY_IF_NOT_NULL(address_str);
    MACRO_DELETE_ARRAY_IF_NOT_NULL(lat_str);
    MACRO_DELETE_ARRAY_IF_NOT_NULL(lng_str);
    // Check if parsing failed
    if (errno == ERANGE) {
        return -1;
    }
    // Success is determined by parse
    return err;
}
