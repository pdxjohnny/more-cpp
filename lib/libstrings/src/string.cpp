#include "strings.h"

/*
 * Constructor
 */
strings::string::string() : data(NULL) {}

/*
 * Start with a character array
 */
strings::string::string(const char * init) : data(NULL) {
    operator=(init);
}

/*
 * Start with a string
 */
strings::string::string(const strings::string & init) : data(NULL) {
    operator=(init.c_str());
}

/*
 * Join all the strings passed in
 */
strings::string::string(int num, ...) : data(NULL) {
    int added;
    va_list args;
    va_start(args, num);
    // Set to the first string
    operator=(va_arg(args, const char *));
    // Append the rest of the strings
    for (added = num; added > 1; --added) {
        operator+=(va_arg(args, const char *));
    }
    va_end(args);
}

/*
 * Free our string
 */
strings::string::~string() {
    clr();
}

/*
 * Free our string if it is not NULL
 */
void strings::string::clr() {
    if (data != NULL) {
        delete[] data;
        data = NULL;
    }
    return;
}

/*
 * Returns the character array we hold
 */
const char * strings::string::c_str() const {
    return data;
}

/*
 * Set our internal string
 */
strings::string & strings::string::operator = (const char * copy) {
    clr();
    if (copy != NULL) {
        data = new char[strlen(copy) + 1];
        strcpy(data, copy);
    }
    return *this;
}

strings::string & strings::string::operator = (const strings::string & copy) {
    return operator=(copy.c_str());
}

/*
 * Concatinate to the string
 */
strings::string & strings::string::operator += (const char * append) {
    int data_size = 0;
    int append_size = 0;
    if (data != NULL) {
        data_size = strlen(data);
    }
    if (append != NULL) {
        append_size = strlen(append);
    }
    if (data_size + append_size > 0 && data != NULL && append != NULL) {
        char * tmp = new char[data_size + append_size + 1];
        strcpy(tmp, data);
        strcat(tmp, append);
        clr();
        data = tmp;
    }
    return *this;
}

strings::string & strings::string::operator += (const strings::string & append) {
    return operator+=(append.c_str());
}

/*
 * Combine strings
 */
strings::string   strings::operator +  (const strings::string & one, const strings::string & two) {
    return strings::string(2, one.c_str(), two.c_str());
}

strings::string   strings::operator +  (const strings::string & one, const char * two) {
    return strings::string(2, one.c_str(), two);
}

strings::string   strings::operator +  (const char * one, const strings::string & two) {
    return strings::string(2, one, two.c_str());
}

/*
 * Compare strings
 */

bool strings::operator <  (const strings::string & one, const strings::string & two) {
    return (0 <  strcmp(one.c_str(), two.c_str()));
}

bool strings::operator <  (const strings::string & one, const char * two) {
    return (0 <  strcmp(one.c_str(), two));
}

bool strings::operator <  (const char * one, const strings::string & two) {
    return operator< (two, one);
}

bool strings::operator <= (const strings::string & one, const strings::string & two) {
    return (0 <= strcmp(one.c_str(), two.c_str()));
}

bool strings::operator <= (const strings::string & one, const char * two) {
    return (0 <= strcmp(one.c_str(), two));
}

bool strings::operator <= (const char * one, const strings::string & two) {
    return operator<=(two, one);
}

bool strings::operator >  (const strings::string & one, const strings::string & two) {
    return (0 >  strcmp(one.c_str(), two.c_str()));
}

bool strings::operator >  (const strings::string & one, const char * two) {
    return (0 >  strcmp(one.c_str(), two));
}

bool strings::operator >  (const char * one, const strings::string & two) {
    return operator> (two, one);
}

bool strings::operator >= (const strings::string & one, const strings::string & two) {
    return (0 >= strcmp(one.c_str(), two.c_str()));
}

bool strings::operator >= (const strings::string & one, const char * two) {
    return (0 >= strcmp(one.c_str(), two));
}

bool strings::operator >= (const char * one, const strings::string & two) {
    return operator>=(two, one);
}

bool strings::operator != (const strings::string & one, const strings::string & two) {
    return (0 != strcmp(one.c_str(), two.c_str()));
}

bool strings::operator != (const strings::string & one, const char * two) {
    return (0 != strcmp(one.c_str(), two));
}

bool strings::operator != (const char * one, const strings::string & two) {
    return operator!=(two, one);
}

bool strings::operator == (const strings::string & one, const strings::string & two) {
    return (0 == strcmp(one.c_str(), two.c_str()));
}

bool strings::operator == (const strings::string & one, const char * two) {
    return (0 == strcmp(one.c_str(), two));
}

bool strings::operator == (const char * one, const strings::string & two) {
    return operator==(two, one);
}

/*
 * Displays a string, up to that string to implement string::display
 * this is for showing the user the current strings
 */
std::ostream & strings::operator << (std::ostream & out, const strings::string & display) {
    out << display.c_str();
    return out;
}
