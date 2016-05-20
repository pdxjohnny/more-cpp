/*
 * John Andersen
 * File: study/src/study.cpp
*/
#include "study.h"

int main(int argc, char ** argv, char ** env) {
    // Holds everything we are studying
    study::study_guide guide;
    // The first agrument should be the name of the category we want to study
    strings::string category;
    strings::string action;
    if (argc < 2) {
        errno = EINVAL;
        MACRO_LOG_FATAL("Usage: %s [add|study] [category]", argv[0]);
    }
    action = argv[1];
    if (action == "add") {
        study::task add;
        add.prompt_input(std::cout);
        std::cin >> add;
        std::cout << "Task to add:" << std::endl << add << std::endl;
        guide += add;
    } else if (action == "study") {
        if (argc < 3) {
            errno = EINVAL;
            MACRO_LOG_FATAL("Usage: %s [add|study] [category]", argv[0]);
        }
        category = argv[2];
    } else {
        MACRO_LOG_FATAL("You must choose to either \'add\' a task or \'study\', you said \'%s\'", action.c_str());
    }
    // Let them know how it all looks beore they exit
    std::cout << "--- Current State Of Your Tasks ----" << std::endl << guide;
    return EXIT_SUCCESS;
}
