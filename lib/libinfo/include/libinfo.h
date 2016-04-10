#ifndef LIBINFO

#define LIBINFO

#define INFO_ADDRESS_DELIM ", "
#define INFO_ADDRESS_DONT_HAVE "n/a"
#define INFO_EARTHS_RADIUS_IN_MILES 3959.0

namespace info {
    // Test functions sould return 42
    int test();
    // Classes that are info related
    class address;
    class location;
};

// An address consists of the country zip etc.
class info::address {
    public:
        // Constuctors and destructors
        address();
        // If you wish to initiallize with members set this is your constuctor
        address(int, const char *, const char *, const char *, const char *);
        ~address();
        // Erases any daat we are holding
        void clear();
        // The length of what the address formated as a string will be
        int address_string_length();
        // Formats itself as a string
        // Returns -1 if it failed
        int address_to_string(char * buffer, int buffer_size);
        // Parses an address from a NULL terminated string
        // Returns -1 if all fields could not be found
        int address_from_string(const char *);
    private:
        // Zip code
        int zip;
        // Street which contains the house / aptment number
        char * street;
        // The city that street is in
        char * city;
        // State or provence within county
        char * state_or_province;
        // The country
        char * country;
};

// A location can be a set of longitude and latitude cordinates or an address
class info::location : public info::address {
    public:
        // Constuctors and destructors
        location();
        location(int, const char *, const char *, const char *, const char *);
        location(double lng, double lat);
        ~location();
        // Clears address and lat lng data
        void clear();
        // Sets the location to be an address
        // Returns -1 if address was invalid
        int address_from_string(const char *);
        // Sets the values pased in to be the longitude and latitude that we
        // are using
        // Returns -1 if we dont have cordinates
        int lnglat(double * lng, double * lat);
        // Sets the location to be a pair of longitude and latidue cordinates
        // Returns -1 if cordinates were invalid
        int lnglat(double, double);
        // Calculate the distance from another location in miles
        float distance_in_miles(const location &);
        // Attempts to find the address of the cordinates which we are
        // currently set to
        // Returns -1 if the address could not be found
        int find_address();
    private:
        // lng lat cordinates
        double lng;
        double lat;
};

#endif

