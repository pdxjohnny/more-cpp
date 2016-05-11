Study Guide
---

    I was able to do some operator overloading in the card game program so this
will just be applying it in a different way. The way I have my data structres
written I could finish and turn in this program fairly quickly, perhaps even on
time. But I think now is probably a good time to do the ballenced tree because
I have already strated it in cpp and just didn't have time to finish it. All my
data structures are templated so I could just say `lll<bst<study::task>>` and
have a linked list of binary search trees of study tasks. I will probably
inherit from that templated type to be my manager of the tasks.

`class study_guide : public lll<bst<study::task>>`

    Then if the task class knows which category it is apart of then the +=
operator when used as `study_guide += task` would be able to add the task to
the correct category. The task could impliment the comparison operators to
determine its priority in relation to other tasks so that it can be sorted in
the bst. The task should implement the insertion and extracion operators so
that we can print the task and take in its data. To avoid prompting from within
the task we should ask that the data be inserted in a certain format. For
example the first line being the category and the next being the task name and
the rest being the task.
    For the balenced tree I think I'm going to go with a 2-3 tree. I tried to
do a red black a while ago but 163 was over a year ago so I don't remember how
it was supposed to work. I looked online but felt like there was no good
explination other than some code I found which I did not want to use as an
example because I don't want to copy anything. The 2-3 tree I have plenty of
notes on and shouldn't be too bad to implement.
    I already wrote my string class and its test cases, that was quick and
easy. I found when writing it that a neet timesaver is to call the operator= in
the contructor with a const char array and copy constructor. That way I dont
have to write the code twice. I also implemented all of the comparisons with
const char arrays and made the creation of the string from a const char array
explicit.
