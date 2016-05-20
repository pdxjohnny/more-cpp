#include "study.h"


/*
 * Create a task which by default is an Ace of Hearts just because we need a
 * default
 */
study::task::task() : priority(0), complete(false) {}

/*
 * Copy another task
 */
study::task::task(const task & copy) : priority(copy.priority), complete(copy.complete), title(copy.title), category(copy.category), description(copy.description) {}

/*
 * Destroy the task, no point this wont do anything as it is just two chars
 */
study::task::~task() {}

/*
 * Copy the task data
 */
study::task & study::task::operator=(const task & copy) {
    priority = copy.priority;
    complete = copy.complete;
    title = copy.title;
    category = copy.category;
    description = copy.description;
    return *this;
}

/*
 * Lets us compare our priority to that of another task
 */
bool study::operator <  (const study::task & one, const study::task & two) {
    return (one.priority <  two.priority);
}
bool study::operator <= (const study::task & one, const study::task & two) {
    return (one.priority <= two.priority);
}
bool study::operator >  (const study::task & one, const study::task & two) {
    return (one.priority >  two.priority);
}
bool study::operator >= (const study::task & one, const study::task & two) {
    return (one.priority >= two.priority);
}
bool study::operator != (const study::task & one, const study::task & two) {
    return (one.priority != two.priority);
}
bool study::operator == (const study::task & one, const study::task & two) {
    return (one.priority == two.priority);
}

/*
 * Displays without colors or unicode
 */
std::ostream & study::task::save(std::ostream & out) {
    if (complete == true) {
        out << "Complete";
    } else {
        out << "In Progress";
    }
    out << std::endl;
    out << title << std::endl;
    out << "---- Description ----" << std::endl;
    out << description;
    return out;
}

/*
 * Displays a task
 */
std::ostream & study::operator<<(std::ostream & out, study::task & task) {
    if (task.complete == true) {
        out << MACRO_GREEN "✔ Complete " MACRO_RESET;
    } else {
        out << MACRO_RED "✘ In Progress " MACRO_RESET;
    }
    out << task.title << std::endl;
    out << "---- Description ----" << std::endl;
    out << task.description;
    return out;
}

/*
 * Parses a task
 */
std::istream & study::operator>>(std::istream & in, study::task & task) {
    const int buffer_size = 500;
    char * buffer = new char[buffer_size];
    int i;
    for (i = 0; in.eof() == false; ++i) {
        memset(buffer, 0, buffer_size);
        if (in.eof()) {
            return in;
        }
        in.getline(buffer, buffer_size);
        switch (i) {
        case 0:
            task.complete = false;
            if (strings::tobool(buffer) == true) {
                task.complete = true;
            }
            break;
        case 1:
            task.title = buffer;
            break;
        default:
            if (0 != strcmp(buffer, "---- Description ----")) {
                task.description += buffer;
            }
            break;
        }
    }
    delete[] buffer;
    return in;
}
