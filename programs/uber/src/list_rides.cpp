#include "uber.h"

int list_rides(int argc, char ** argv, uber::car *& standard, uber::car *& premium, uber::car *& group, uber::rides & rides) {
    return rides.print();
}
