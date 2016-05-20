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
 * Displays only completion status and title
 */
std::ostream & study::task::brief(std::ostream & out) {
    if (complete == true) {
        out << MACRO_GREEN "✔ Complete " MACRO_RESET;
    } else {
        out << MACRO_RED "✘ In Progress " MACRO_RESET;
    }
    out << title;
    return out;
}

/*
 * Displays without colors or unicode
 */
void study::task::save(const char * dir) {
    strings::string path(dir);
    path += '/';
    path += category;
    // Make the directory for the category
    mkdir(path.c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
    path += '/';
    path += title;
    // Open the file
    std::ofstream out;
    out.open(path.c_str());
    if (out.is_open()) {
        if (complete == true) {
            out << "Complete";
        } else {
            out << "In Progress";
        }
        out << std::endl << priority << std::endl;
        out << category << std::endl;
        out << title << std::endl;
        out << "---- Description ----" << std::endl;
        out << description;
    }
    // Close the file
    out.close();
    return;
}

/*
 * Displays a task
 */
std::ostream & study::operator<<(std::ostream & out, study::task & task) {
    task.brief(out);
    out << std::endl;
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
            task.priority = strings::toint(buffer);
            break;
        case 2:
            task.category = buffer;
            break;
        case 3:
            task.title = buffer;
            break;
        default:
            if (0 != strcmp(buffer, "---- Description ----")) {
                task.description += buffer;
                task.description += '\n';
            }
            break;
        }
    }
    // Prevent us from adding a million newlines over time
    task.description[task.description.length() - 1] = '\0';
    delete[] buffer;
    return in;
}

/*
 * Prompt for input
 */
std::ostream & study::task::prompt_input(std::ostream & out) const {
    out << "Format of task is as follows:" << std::endl;
    out << "Complete (yes, no, true, false, complete, incomplete)" << std::endl;
    out << "Priority (integer value)" << std::endl;
    out << "Category (linked lists, history of denmark)" << std::endl;
    out << "Title" << std::endl;
    out << "Description (as many lines as you need, eof to stop)" << std::endl;
    return out;
}

/*
 * Returns the category
 */
const char * study::task::get_category() const {
    return category.c_str();
}
