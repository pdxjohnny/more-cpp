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
 * Displays a task
 */
std::ostream & study::operator<<(std::ostream & out, study::task & task) {
    if (task.complete == true) {
        out << MACRO_GREEN "✔" MACRO_RESET;
    } else {
        out << MACRO_RED "✘" MACRO_RESET;
    }
    out << task.title << std::endl;
    out << "---- Description ----" << std::endl;
    out << task.description;
    return out;
}

/*
 * Parses a task
 */
std::ostream & study::operator>>(std::ostream & out, study::task & task) {
    if (task.complete == true) {
        out << MACRO_GREEN "✔" MACRO_RESET;
    } else {
        out << MACRO_RED "✘" MACRO_RESET;
    }
    out << task.title << std::endl;
    out << "---- Description ----" << std::endl;
    out << task.description;
    return out;
}
