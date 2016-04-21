#include "uber.h"


int user_action(int argc, char ** argv, uber::car *& standard, uber::car *& premium, uber::car *& group, uber::rides & rides) {
    // Confifure the functions that we can call
    bst<int(*)(int, char **, uber::car *&, uber::car *&, uber::car *&, uber::rides &)> commands;
    commands["help"] = help;
    // The command to call
    char help_cmd[] = "help";
    char * cmd = help_cmd;
    if (argc > 1) {
        cmd = argv[1];
    }
    if (commands.contains(cmd)) {
        return commands[cmd](argc, argv, standard, premium, group, rides);
    }
    return commands[help_cmd](argc, argv, standard, premium, group, rides);
}

// Im using fd becuase then I can read from a socket or a file and if I have
// extra time then it will be a socket
int read_in_cars(int fd, uber::car *& standard, uber::car *& premium, uber::car *& group) {
    // Make sure fd is valid
    if (fd < 0) {
        return -1;
    }
    // For reading from fd
    int bytes_read = 0;
    const int buffer_size = 300;
    char * buffer = new char [buffer_size + 1];
    memset(buffer, 0, sizeof(char) * buffer_size + 1);
    buffer[buffer_size] = '\0';
    // Car info
    uber::car temp;
    // Read in cars until EOF
    do {
        // Read in the line
        bytes_read = strings::readline(fd, buffer, buffer_size);
        // If we read nothing then bail
        if (bytes_read < 1) {
            break;
        }
        // Make a car out of it
        if (temp.car_from_string(buffer) != EXIT_SUCCESS) {
            MACRO_LOG_ERROR("Failed to read in car \'%s\'", buffer);
            continue;
        }
        // Put that car where it should be
        switch (uber::car_type(temp)) {
        case UBER_CAR_PREMIUM:
            if (premium == NULL) {
                premium = new uber::car(temp);
            } else {
                premium->add(new uber::car(temp));
            }
            break;
        case UBER_CAR_GROUP:
            if (group == NULL) {
                group = new uber::car(temp);
            } else {
                group->add(new uber::car(temp));
            }
            break;
        case UBER_CAR_STANDARD:
        default:
            if (standard == NULL) {
                standard = new uber::car(temp);
            } else {
                standard->add(new uber::car(temp));
            }
            break;
        }
    } while (bytes_read > 1);
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
    char cars_file[] = "static/cars.txt";
    char rides_file[] = "static/rides.txt";
    int cars_fd = 0;
    int rides_fd = 0;
    // Read in the cars
    cars_fd = open(cars_file, O_RDONLY);
    if (cars_fd > -1) {
        read_in_cars(cars_fd, standard, premium, group);
        close(cars_fd);
    } else {
        MACRO_LOG_ERROR("Could not open \'%s\' file to load cars from", cars_file);
    }
    // Load the rides
    rides_fd = open(rides_file, O_RDONLY);
    if (rides_fd > -1) {
        // rides.load(rides_fd);
        close(rides_fd);
    } else {
        MACRO_LOG_ERROR("Could not open \'%s\' file to load rides from", rides_file);
    }
    // Act on what the user wants
    user_action(argc, argv, standard, premium, group, rides);
    // Clear the existing save files
    rides_fd = open(rides_file, O_CREAT | O_WRONLY, S_IRUSR | S_IWUSR);
    if (rides_fd < 0) {
        MACRO_LOG_ERROR("Could not open \'%s\' file to save rides to", rides_file);
    }
    cars_fd = open(cars_file, O_CREAT | O_WRONLY, S_IRUSR | S_IWUSR);
    if (cars_fd < 0) {
        MACRO_LOG_ERROR("Could not open \'%s\' file to save cars to", cars_file);
    }
    // Save the rides
    rides.save(rides_fd);
    // Save the cars
    if (standard != NULL) {
        standard->save(cars_fd);
        standard->destroy();
        delete standard;
    }
    if (premium != NULL) {
        premium->save(cars_fd);
        premium->destroy();
        delete premium;
    }
    if (group != NULL) {
        group->save(cars_fd);
        group->destroy();
        delete group;
    }
    // Close the files
    if (rides_fd > -1) {
        close(rides_fd);
    }
    if (cars_fd > -1) {
        close(cars_fd);
    }
    return EXIT_SUCCESS;
}
