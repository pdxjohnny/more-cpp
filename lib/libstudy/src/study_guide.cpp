#include "study.h"

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
    return *this;
}

// Displays everything in the tree
void study::study_guide::display(std::ostream & out) {
    int i;
    for (i = size() - 1; i >= 0; --i) {
        operator[](i).display(out);
        out << std::endl;
    }
    return;
}
