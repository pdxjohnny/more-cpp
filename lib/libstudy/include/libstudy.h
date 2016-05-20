/*
 * John Andersen
 * File: libtask/include/libtask.h
*/
#include <exception>
#include <iostream>

#include <libstrings.h>
#include <liblll.h>
#include <libtree23.h>

// Tasks
namespace study {
    // Card coingtians the value and suit
    class task;
    // A tasks of task
    class tasks;
    // A study_guide of task
    class study_guide;

    // Compare
    bool operator <  (const study::task &, const study::task &);
    bool operator <= (const study::task &, const study::task &);
    bool operator >  (const study::task &, const study::task &);
    bool operator >= (const study::task &, const study::task &);
    bool operator != (const study::task &, const study::task &);
    bool operator == (const study::task &, const study::task &);

    // Display a task
    std::ostream & operator << (std::ostream &, study::task &);
    std::istream & operator >> (std::istream &, study::task &);
};

// A task is what we are going to do and it can be marked as complete
class study::task {
    public:
        // Constructor
        task();
        task(const task & copy);
        // Destroy the task
        ~task();
        // Copy the task data
        task & operator=(const task & copy);
        // Lets us compare our value to that of another task
        friend bool operator <  (const study::task &, const study::task &);
        friend bool operator <= (const study::task &, const study::task &);
        friend bool operator >  (const study::task &, const study::task &);
        friend bool operator >= (const study::task &, const study::task &);
        friend bool operator != (const study::task &, const study::task &);
        friend bool operator == (const study::task &, const study::task &);
        // Just output completion status and title
        std::ostream & brief(std::ostream & out);
        // Outputs the task
        std::ostream & save(std::ostream & out);
        friend std::ostream & study::operator << (std::ostream &, study::task &);
        // Parses in the task
        friend std::istream & study::operator >> (std::istream &, study::task &);
        // Lets the user know the format of the input
        std::ostream & prompt_input(std::ostream & out) const;
    private:
        int priority;
        bool complete;
        strings::string title;
        strings::string category;
        strings::string description;
};

// All of the tasks in prioritized order
class study::tasks : public tree23<study::task> {
    public:
        // Sets the category
        tasks & operator=(const char * str);
        tasks & operator=(const strings::string & str);
        // Copy all the tasks
        tasks & operator=(const tasks & copy);
        // Display this and all the titles of the tasks it holds
        void display(std::ostream &);
    private:
        // The category of tasks that we hold
        strings::string category;
};

// study::study_guide is a study_guide of task. A study_guide of task is organized by suite. A study_guide
// also can be shuffled so that it can be used for a task game
class study::study_guide : public lll<study::tasks> {
    public:
        // Copy all the tasks
        study_guide & operator=(study_guide & copy);
        // Adds a task to the correct category
        study_guide & operator+=(const task & add);
        // Lets you access a random tasks from the study_guide
        study::task random();
        // Displays all of the tasks titles
        void display(std::ostream &);
};
