#include "strings.h"
#include <iostream>

void strings::toupper(char * buffer) {
    int i;
    for (i = std::strlen(buffer) - 1; i >= 0; --i) {
        buffer[i] = std::toupper(buffer[i]);
    }
}

bool strings::tobool(const char * buffer) {
    char copy[strlen(buffer) + 1];
    std::strcpy(copy, buffer);
    strings::toupper(copy);
    if (0 == strcmp(copy, "YES") ||
            0 == strcmp(copy, "✔") ||
            0 == strcmp(copy, "Y") ||
            0 == strcmp(copy, "TRUE") ||
            0 == strcmp(copy, "COMPLETE") ||
            0 == strcmp(copy, "DONE")) {
        return true;
    }
    return false;
}

int strings::toint(const char * buffer) {
    return std::strtol(buffer, NULL, 10);
}
