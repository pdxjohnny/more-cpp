#include "uber.h"


uber::car::car(int year, const char * make, const char * model, const char * plate_number, const char * vin) : transport::car(year, make, model, plate_number, vin) {
}

char uber::car::match(circle * node) {
    uber::car * car_node = dynamic_cast<uber::car *>(node);
    if (0 == (strcmp(this->make(), car_node->make()) +
                strcmp(this->model(), car_node->model()))) {
        return 1;
    }
    return 0;
};

char uber::car::sort(circle * node) {
    uber::car * car_node = dynamic_cast<uber::car *>(node);
    if (0 >= (strcmp(this->make(), car_node->make()) +
                strcmp(this->model(), car_node->model()))) {
        return CIRCLE_NEXT;
    }
    return CIRCLE_HERE;
};
