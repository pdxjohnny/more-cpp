#include "cards.h"

void cards::clear(std::ostream & out) {
    const int lines = 100;
    int i;
    for (i = lines - 1; i >= 0; --i) {
        out << std::endl;
    }
}
