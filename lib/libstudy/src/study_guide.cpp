#include "study.h"

// Remove all the nodes from all the trees
study::study_guide::~study_guide() {
    int i;
    // Save everything
    mkdir(study::SAVE_DIR, S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
    // Delete everythign from memory
    for (i = 0; i < size(); ++i) {
        // Only save if we were able to make the directory
        study::tasks * collection = &this->operator[](i);
        collection->save(study::SAVE_DIR);
        collection->remove_all();
    }
}

// Copy all the study_guide
study::study_guide & study::study_guide::operator=(study_guide & copy) {
    if (this == &copy) {
        return *this;
    }
    int i;
    for (i = 0; i < copy.size(); ++i) {
        this->operator[](i) = copy[i];
    }
    return *this;
}

// Add to the appropriate tasks tree
study::study_guide & study::study_guide::operator+=(const study::task & copy) {
    this->operator[](copy.get_category()) += copy;
    return *this;
}

// Access a collection of tasks
study::tasks & study::study_guide::operator[](const int index) {
    return lll<study::tasks>::operator[](index);
}

study::tasks & study::study_guide::operator[](const char * str) {
    int i;
    for (i = size() - 1; i >= 0; --i) {
        study::tasks * collection = &operator[](i);
        if (*collection == str) {
            return *collection;
        }
    }
    // Not found so add
    study::tasks add(str);
    lll<study::tasks>::operator+=(add);
    return operator[](size() - 1);
}

study::tasks & study::study_guide::operator[](const strings::string & str) {
    return operator[](str.c_str());
}

// Displays everything in the tree
void study::study_guide::display(std::ostream & out) {
    int i;
    for (i = size() - 1; i >= 0; --i) {
        operator[](i).display(out);
    }
    return;
}
