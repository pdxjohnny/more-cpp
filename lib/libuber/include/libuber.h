#include <libcircle.h>
#include <libtransport.h>

namespace uber {
    class car;
};

// Our cars need to be a list and a car so we can have lists of them
class uber::car : public circle, public transport::car {
public:
    car(int year, const char * make, const char * model, const char * plate_number, const char * vin);
    virtual char match(circle * node);
    virtual char sort(circle * node);
    char *** unique_makes_models ();
};

