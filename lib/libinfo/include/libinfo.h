#ifndef LIBINFO
#define LIBINFO


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
        ~address();
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
        // The country
        char * country;
        // State or provence within county
        char * state_or_province;
};

// A location can be a set of longitude and latitude cordinates or an address
class info::location {
    public:
        // Constuctors and destructors
        location();
        ~location();
        // Calculate the distance from another location in miles
        float distance_in_miles(const location *&);
        // Format the address as a string and place it in buffer
        // Returns -1 if we dont have the address or if there was a failure
        // formatting
        int address(char * buffer, int buffer_size);
        // Sets the location to be an address
        // Returns -1 if address was invalid
        int address(const char *);
        // Sets the values pased in to be the longitude and latitude that we
        // are using
        // Returns -1 if we dont have cordinates
        int lnglat(double* lng, double * lat);
        // Sets the location to be a pair of longitude and latidue cordinates
        // Returns -1 if cordinates were invalid
        int lnglat(double, double);
        // Attempts to find the address of the cordinates which we are
        // currently set to
        // Returns -1 if the address could not be found
        int find_address();
    private:
        // lng lat cordinates
        double lng;
        double lat;
        // Address
        info::address addr;
};

#endif

