/*
 * John Andersen
 * File: study/src/study.cpp
*/
#include "study.h"

int study_interactive(study::study_guide & guide) {
    std::cout << "Here are some tasks for you to study" << std::endl;
    std::cout << "Just type \"Complete\" or \"not complete\" to";
    std::cout << " mark the task as that. Completed tasks will not show";
    std::cout << " up when you study this category again" << std::endl;
    study::tasks * collection = NULL;
    try {
        collection = &guide.random();
    } catch (index_out_of_range err) {
        MACRO_LOG_FATAL("You need to add some tasks before you can study them \'%s\'", err.what());
    }
    study::task * curr = NULL;
    bool studied_something = false;
    const int buffer_size = 100;
    char * buffer = new char[buffer_size];
    int i;
    // Go through from highest to lowest priortiy
    for (i = collection->size() - 1; i >= 0; --i) {
        // Get the task and display it if it is not complete
        curr = &collection->operator[](i);
        if (curr->completed() == false) {
            // Track if they have studied anything
            studied_something = true;
            std::cout << *curr;
            // Read in their response
            std::cin.getline(buffer, buffer_size);
            // If they said they are done studying it then mark it as complete
            if (strings::tobool(buffer) == true) {
                *curr = true;
            }
        }
    }
    if (studied_something == false) {
        std::cout << std::endl << "Great Job! you studied everything in this" <<
            " category! Add more taskes to study more or run again to see" <<
            " which category you'll get next" << std::endl << std::endl;
    }
    delete[] buffer;
    return EXIT_SUCCESS;
}

int main(int argc, char ** argv, char ** env) {
    // In case thers an error it is stored in this so we can check
    int err;
    // Holds everything we are studying
    study::study_guide guide;
    // The first agrument should be the name of the category we want to study
    strings::string action;
    if (argc < 2) {
        errno = EINVAL;
        MACRO_LOG_FATAL("Usage: %s [add|list|study]", argv[0]);
    }
    action = argv[1];
    if (action == "add") {
        study::task add;
        add.prompt_input(std::cout);
        std::cin >> add;
        std::cout << "Task to add:" << std::endl << add << std::endl;
        guide += add;
    } else if (action == "study") {
        err = study_interactive(guide);
        if (err != EXIT_SUCCESS) {
            return err;
        }
    } else if (action == "list") {
        std::cout << guide;
        return EXIT_SUCCESS;
    } else {
        MACRO_LOG_FATAL("You must choose to either \'add\' a task or \'study\', you said \'%s\'", action.c_str());
    }
    // Let them know how it all looks beore they exit
    std::cout << "--- Current State Of Your Tasks ----" << std::endl << guide;
    return EXIT_SUCCESS;
}
