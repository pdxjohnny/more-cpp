/*
 * John Andersen
 * File: libstrings/test/file.cpp
*/

#include "strings.h"


int test_strings_readline() {
    // Set up the pipe
    int fd[2];
    pipe(fd);
    // Write the test data to it
    char test_lines[] = "hello test\nthis is person\ngood day\n";
    write(fd[1], test_lines, strlen(test_lines));
    // Create the buffer
    char buffer[11];
    // Use the function and make sure we are getting what we expect
    strings::readline(fd[0], buffer, 11);
    MACRO_TEST_STR_EQ(buffer, "hello test");
    strings::readline(fd[0], buffer, 11);
    MACRO_TEST_STR_EQ(buffer, "this is pe");
    strings::readline(fd[0], buffer, 11);
    MACRO_TEST_STR_EQ(buffer, "good day");
    // All is well
    return EXIT_SUCCESS;
}
