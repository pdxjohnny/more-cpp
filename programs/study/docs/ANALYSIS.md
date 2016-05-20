Analysis Of Study Guide Program
---

This program used operator overloading heavily. I created a string class where
it came in handy a lot, as well as with the program itself. I frequently used
the subscript operator to provide access to the data stored in my classes. The
+= operator because a replacement for any `add` methods, and I found the
overloading the equals operator was conveniant for classes where I wanted
setter functionality. The hardest part of this was the blanced tree. I did the
2-3 tree, it has been over a year since I took 163 and I couldnt find my notes
on it so it was rather difficult to figure out what it was supposed to do.

After spending my hours looking only at descriptions of how it should work and
visualisations and videos I finally tried the good old draw a million trees
trick. This did it for me right away. I figured out how to create the tree
fairly quickly after that.

One thing that I would have liked to implement would be keeping track in the
categories of tasks on whether they have all been completed or not. This would
prevent the random category we get from being one that we have already done and
having to run the program a bunch of times to get to a one thats not complete.

The insertion operator and extraction operator came in handy for displaying and
saving the data. Karla mentioned in class that she had told someone that they
could use the destructor to make sure the data always saves by saving from
within the destructor! So thats what I did and I loaded data from the
contructor. It made it real quick and easy. If I were to do it again I would
have those as seperate fucntions and have the contructor take a paramater of
the directory to save and load from but I needed to hurry up and finish.

If I had more time I would also add the ability to go over all the tasks and re
mark them as not done. This is all easy to do but it would just a take a few
minutes and be a loop through.

I think I did a pretty good job of OOP. The task has a few strings classes as
data and some ints. The tasks class was derived from a 2-3 tree of task
(templated, `tree23<task>`). The `study_guide` was an lll of tasks
(`lll<tasks>`). That was all the classes I needed for this.

The comparison operators are used on the templated data type in the 2-3 tree.
So any classs (like study::task) which implements the comparison operators can
be used with the tree.
