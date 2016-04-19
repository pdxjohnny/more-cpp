#include "uber.h"


uber::car::car(car & copy) : transport::car(copy) {}

uber::car::car(int year, const char * make, const char * model, const char * plate_number, const char * vin) : transport::car(year, make, model, plate_number, vin) {}

char uber::car::match(circle * node) {
    uber::car * car_node = dynamic_cast<uber::car *>(node);
    if (0 == (strcmp(this->make(), car_node->make()) +
                strcmp(this->model(), car_node->model()))) {
        return 1;
    }
    return 0;
}

char uber::car::sort(circle * node) {
    uber::car * car_node = dynamic_cast<uber::car *>(node);
    if (0 >= (strcmp(this->make(), car_node->make()) +
                strcmp(this->model(), car_node->model()))) {
        return CIRCLE_NEXT;
    }
    return CIRCLE_HERE;
}

// Because we cant do inline callbacks
class uber::car::oneach_unique_makes_models : public circle::each {
public:
    int do_func(circle * node) {
        uber::car * curr = dynamic_cast<uber::car *>(node);
        if (curr == NULL) {
            // This should never happen
            return -3;
        }
        // Make sure that there is a make and model
        if (curr->make() == NULL || curr->model() == NULL) {
            return -2;
        }
        // Join the make and model
        char * make = curr->make();
        char * model = curr->model();
        char ** mm_join[] = {&make, &model, NULL};
        int mm_length = strings::join_length(mm_join, "/", "unavailable");
        char mm[mm_length];
        MACRO_CANT_EQ(strings::join(mm, mm_join, "/", "unavailable", mm_length), -1);
        // Add it to the combos we have already
        combos[mm] = 1;

        return EXIT_SUCCESS;
    }
    // Stores the make model combinations it has found so far
    bst<char> combos;
};

// Returns unique makes and models as a NULL terminated array. Dont forget to
// delete them.
char *** uber::car::unique_makes_models () {
    uber::car::oneach_unique_makes_models callback;
    this->oneach(callback);
    // char *** keys = callback.combos.keys();
    // MACRO_DELETE_ARRAY_OF_STRINGS(keys);
    return callback.combos.keys();
}
