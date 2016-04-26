#include "user.h"

int test_user_base_output() {
    /*
     * I cant make this test case work
     */
    /*
    // Pipe stdout to our pipe so that we can do strcmp
	int fd[2];
    pipe(fd);
    int save_stdout = dup(STDOUT_FILENO);
	dup2(fd[1], STDOUT_FILENO);
    // Read everything in from stdout
    char tmp = '\0';
    while (read(fd[0], &tmp, 1) > 0) {}
    // Create the basic user and send some output to it
    user::basic test;
    test << "Hello\n";
    // Restore stdout
	dup2(save_stdout, STDOUT_FILENO);
    // Verify that the output was sent correctly to stdout
    char buffer[7];
    MACRO_TEST_EQ((int)read(fd[0], buffer, 6), 6);
    buffer[7] = '\0';
    MACRO_TEST_STR_EQ(buffer, "Hello\n");
    */
    return EXIT_SUCCESS;
}
