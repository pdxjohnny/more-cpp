#include "uber.h"


int user_action(int argc, char ** argv, uber::car *& standard, uber::car *& premium, uber::car *& group, uber::rides & rides) {
}

// Im using fd becuase then I can read from a socket or a file and if I have
// extra time then it will be a socket
int read_in_cars(int fd, uber::car *& standard, uber::car *& premium, uber::car *& group) {
    // For reading from fd
    int bytes_read = 0;
    const int buffer_size = 300;
    char * buffer = new char [buffer_size];
    // Car info
    uber::car temp;
    uber::car * add = NULL;
    uber::car * add_to = NULL;
    // Read in cars until EOF
    do {
        // Read in the line
        bytes_read = strings::readline(fd, buffer, buffer_size);
        // If we read nothing then bail
        if (bytes_read < 0) {
            break;
        }
        // Make a car out of it
        temp.car_from_string(buffer);
        // Put that car where it should be
        switch (uber::car_type(temp)) {
        case UBER_CAR_PREMIUM:
            add_to = premium;
            break;
        case UBER_CAR_GROUP:
            add_to = group;
            break;
        default:
        case UBER_CAR_STANDARD:
            add_to = standard;
            break;
        }
        // Allocate the car
        add = new uber::car(temp);
        // Determine how to add the car
        if (add_to == NULL) {
            add_to = add;
        } else {
            add_to->add(add);
        }
    } while (bytes_read != 0);
    // Free the buffer
    MACRO_DELETE_ARRAY_IF_NOT_NULL(buffer);
    return EXIT_SUCCESS;
}

int main(int argc, char ** argv, char ** env) {
    // The types of cars available
    uber::car * standard = NULL;
    uber::car * premium = NULL;
    uber::car * group = NULL;
    // If the user wants to make a trip then store it here
    uber::rides rides;
    // The files we will store data in
    char * cars_file;
    char * rides_file;
    // Read in the cars
    int fd = open(cars_file, O_RDONLY);
    read_in_cars(fd, standard, premium, group);
    close(fd);
    // Act on what the user wants
    user_action(standard, premium, group, rides);
    // Clear the existing save files
    int rides_fd = open(rides_file, O_WRONLY);
    int cars_fd = open(cars_file, O_WRONLY);
    // Save the rides
    rides.save(rides_fd);
    // Save the cars
    standard.save(cars_fd);
    premium.save(cars_fd);
    group.save(cars_fd);
    // Close the files
    close(rides_fd);
    close(cars_fd);
    return 0;
}
