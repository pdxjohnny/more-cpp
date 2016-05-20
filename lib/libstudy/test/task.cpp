#include "study.h"

int test_study_task_save_parse() {
    study::task test;
    // These are just for testing
    std::ostringstream out;
    std::istringstream in;
    // Send it out
    test.save(out);
    in.str(out.str());
    in >> test;
    return EXIT_SUCCESS;
}
