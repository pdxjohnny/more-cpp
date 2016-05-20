#include "study.h"

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
