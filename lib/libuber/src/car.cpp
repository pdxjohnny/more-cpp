#include "uber.h"


uber::car::car() {}

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
    return callback.combos.keys();
}

// Because we cant do inline callbacks
class uber::car::oneach_save : public circle::each {
public:
    int do_func(circle * node) {
        uber::car * curr = dynamic_cast<uber::car *>(node);
        if (fd < 0) {
            // Bad file descriptor
            return -2;
        }
        const int buffer_length = 500;
        char buffer[buffer_length];
        buffer[buffer_length] = '\0';
        curr->car_to_string(buffer, buffer_length);
        write(this->fd, buffer, strlen(buffer));
        write(this->fd, "\n", 1);
        return EXIT_SUCCESS;
    }
    // File we are saving to
    int fd;
};


// Save cars to a file
int uber::car::save(int fd) {
    uber::car::oneach_save callback;
    callback.fd = fd;
    this->oneach(callback);
    return EXIT_SUCCESS;
}
