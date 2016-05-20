#include "study.h"

// Constructor
study::tasks::tasks() {}

// Set the category
study::tasks::tasks(const char * str) : category(str) {}

// Set the category
study::tasks & study::tasks::operator=(const char * str) {
    category = str;
    return *this;
}

// Copy all the tasks
study::tasks & study::tasks::operator=(const strings::string & str) {
    category = str;
    return *this;
}
// Copy all the tasks
study::tasks & study::tasks::operator=(const tasks & copy) {
    if (this == &copy) {
        return *this;
    }
    category = copy.category;
    tree23<study::task>::operator=(copy);
    return *this;
}

// Checks if we are for this category
bool study::operator==(const tasks & collection, const char * str) {
    return (collection.category == str);
}

// Checks if we are for this category
bool study::operator==(const tasks & collection, const strings::string & str) {
    return study::operator==(collection, str.c_str());
}

// Displays everything in the tree
void study::tasks::display(std::ostream & out) {
    out << "Tasks under " << category << std::endl;
    int i;
    for (i = size() - 1; i >= 0; --i) {
        operator[](i).brief(out);
        out << std::endl;
    }
    return;
}

// Remove all the nodes from all the trees
void study::tasks::save(const char * dir) {
    int i;
    // Delete everythign from memory
    for (i = 0; i < size(); ++i) {
        // Only save if we were able to make the directory
        study::task * save_task = &this->operator[](i);
        save_task->save(dir);
    }
}
