#include "uber.h"

uber::rides::rides() {}

uber::rides::~rides() {}

int uber::rides::load(int fd) {
    // Make sure fd is valid
    if (fd < 0) {
        return -1;
    }
    // For reading from fd
    int bytes_read = 0;
    const int buffer_size = 1000;
    char * buffer = new char [buffer_size];
    // Ride info
    uber::ride temp;
    // Read in cars until EOF
    do {
        // Read in the line
        bytes_read = strings::readline(fd, buffer, buffer_size);
        // If we read nothing then bail
        if (bytes_read < 1) {
            break;
        }
        // Make a ride out of it
        if (temp.ride_from_string(buffer) != EXIT_SUCCESS) {
            MACRO_LOG_ERROR("Failed to read in ride \'%s\'", buffer);
            continue;
        }
        // Add the ride to our rides
        time_t treq = temp.time_requested();
        this->get(std::ctime(&treq)) = temp;
    } while (bytes_read != 0);
    // Free the buffer
    MACRO_DELETE_ARRAY_IF_NOT_NULL(buffer);
    return EXIT_SUCCESS;
}

int uber::rides::save(int fd) {
    if (size() < 1) {
        // No ride to save
        return -1;
    }
    const int buffer_length = 1000;
    char buffer[buffer_length];
    unsigned int i;
    for (i = 0; i < size(); ++i) {
        this->get(i).ride_to_string(buffer, buffer_length);
        write(fd, buffer, strlen(buffer));
        write(fd, "\n", 1);
    }
    return EXIT_SUCCESS;
}

int uber::rides::print() {
    if (size() < 1) {
        // No ride to list
        return -1;
    }
    const int buffer_length = 1000;
    char buffer[buffer_length];
    unsigned int i;
    for (i = 0; i < size(); ++i) {
        this->get(i).ride_to_string_readable(buffer, buffer_length);
        MACRO_PRINT("Ride #%d\n%s\n\n", i + 1, buffer);
    }
    return EXIT_SUCCESS;
}
