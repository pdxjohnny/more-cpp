/*
 * John Andersen
 * File: libinfo/include/libinfo.h
*/

#ifndef LIBINFO

#define LIBINFO

#define INFO_ADDRESS_MAX 400
#define INFO_ADDRESS_DELIM ", "
#define INFO_ADDRESS_DONT_HAVE "n/a"

#define INFO_LOCATION_MAX 500
#define INFO_LOCATION_DELIM " . "
#define INFO_LOCATION_DONT_HAVE "n/a"

#define INFO_CONTACT_MAX 500
#define INFO_CONTACT_DELIM ", "
#define INFO_CONTACT_DONT_HAVE "n/a"

#define INFO_CREDIT_CARD_MAX 500
#define INFO_CREDIT_CARD_DELIM ", "
#define INFO_CREDIT_CARD_DONT_HAVE "n/a"

#define INFO_CUSTOMER_MAX 700
#define INFO_CUSTOMER_DELIM "; "
#define INFO_CUSTOMER_DONT_HAVE "n/a"

#define INFO_EARTHS_RADIUS_IN_MILES 3959.0

namespace info {
    // Test functions sould return 42
    int test();
    // Classes that are info related
    class address;
    class location;
    class contact;
    class credit_card;
    class customer;
};

// An address consists of the country zip etc.
class info::address {
    public:
        // Constuctors and destructors
        address();
        address(address &);
        // If you wish to initiallize with members set this is your constuctor
        address(int, const char *, const char *, const char *, const char *);
        ~address();
        address & operator=(const info::address & copy);
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
        location(location &);
        location(int, const char *, const char *, const char *, const char *);
        location(double lng, double lat);
        ~location();
        location & operator=(const info::location & copy);
        // Clears address and lat lng data
        void clear();
        // Sets the location to be an address
        // Returns -1 if address was invalid
        int address_from_string(const char *);
        // Sets address without clearing lnglat
        int update_address_from_string(const char *);
        // Sets the values pased in to be the longitude and latitude that we
        // are using
        // Returns -1 if we dont have cordinates
        int lnglat(double * lng, double * lat);
        // Sets the location to be a pair of longitude and latidue cordinates
        // Returns -1 if cordinates were invalid
        int lnglat(double, double);
        // Sets lntlat without clearing address
        int update_lnglat(double lng, double lat);
        // Calculate the distance from another location in miles
        float distance_in_miles(const location &);
        // Attempts to find the address of the cordinates which we are
        // currently set to
        // Returns -1 if the address could not be found
        int find_address();
        // Formats itself as a string
        // Returns -1 if it failed
        int location_to_string(char * buffer, int buffer_size);
        // Parses an location from a NULL terminated string
        // Returns -1 if all fields could not be found
        int location_from_string(const char *);
    private:
        // lng lat cordinates
        double lng;
        double lat;
};

// Concact info
class info::contact {
    public:
        // Constuctors and destructors
        contact();
        contact(const contact &);
        contact(const char * name, long long int phone);
        ~contact();
        contact & operator=(const info::contact & copy);
        // Formats itself as a string
        // Returns -1 if it failed
        int contact_to_string_readable(char * buffer, int buffer_size);
        int contact_to_string(char * buffer, int buffer_size);
        // Parses an contact from a NULL terminated string
        // Returns -1 if all fields could not be found
        int contact_from_string(const char *);
    private:
        char * name;
        long long int phone;
};

// Credit card info
class info::credit_card {
    public:
        // Constuctors and destructors
        credit_card();
        credit_card(const credit_card &);
        credit_card(long long int, short, short, short);
        ~credit_card();
        credit_card & operator=(const info::credit_card & copy);
        // Formats itself as a string
        // Returns -1 if it failed
        int credit_card_to_string_readable(char * buffer, int buffer_size);
        int credit_card_to_string(char * buffer, int buffer_size);
        // Parses an credit_card from a NULL terminated string
        // Returns -1 if all fields could not be found
        int credit_card_from_string(const char *);
    private:
        long long int number;
        short exp_month;
        short exp_year;
        short cvc;
};

// Customer info
class info::customer : public info::contact, public info::credit_card {
    public:
        // Constuctors and destructors
        customer();
        customer(const customer &);
        customer(info::contact & contact, info::credit_card & credit_card);
        ~customer();
        customer & operator=(const info::customer & copy);
        // Formats itself as a string
        // Returns -1 if it failed
        int customer_to_string_readable(char * buffer, int buffer_size);
        int customer_to_string(char * buffer, int buffer_size);
        // Parses an customer from a NULL terminated string
        // Returns -1 if all fields could not be found
        int customer_from_string(const char *);
};

#endif
