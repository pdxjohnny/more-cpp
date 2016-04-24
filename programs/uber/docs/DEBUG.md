Debugging Uber Clone
---

    I use primarily valgrind to debug. I haven't felt the need to use gdb for
this course, I know how to use it but it just would not be helpful here in my
opinion. Valgrind on the other hand gives me lots of great information, but it
can be devious, more on that later.
    Valgrind allows me to see where I may have forgotten to free memory or
where I forgot to initialize a value. My goal is always to have 0 valgrind
errors. I was able to achive that goal with this program however that could
also mean I didnt test it exhastivly enough.
    My debugging process goes hand in hand with how I organize and write my
programs. From my exxperiance in previous CS courses I have found that I've had
to write many functions over and over again to do the same thing, read a line
from stdin, parse a string, etc. Starting with this assingment I decided that
instead of all the copy pasting I has done before I would create libraries /
archives for the code that I always used. You'll probaly be a little uneasy
when you type make but this is because I haven't ironed out the best way to do
this yet. What happenes is that each library builds all the libraries that it
needs then it builds it self. The same occors for testing.
    I tired to write as many test cases as I could in the time I had. When I
write a test case, it will typacly focus on one method or function of a class
or namespace and try to test different conditions. I use nodemon to rerun the
build whenever I save a file. This way, once I have written my test cases, I go
to the function / methods source and impliment it and work on it until it
passes all the tests. Once it does everything it is supposed to do then I check
it with valgrind. This I dont automate, In the case of the libraries I go
through and run the test binaries with valgrind to make sure that none of the
functions in the libries are leaking any memory, jumping on uninitialized
values, all the good stuf that valgrind informs us about. When I find issues I
go back to the method source and work them out until I get all the tests passed
and no valgrind isseus.
    Writing libraries and testing their functions, classes, and methods allows
me to work at the next level up, the library or program that uses it, with
confidence that whatever bugs I am having are occoring in the scope I am
currently in. However this was not the case with the main cli program I wrote
for this project. This project is called uber, uber does all of the handling of
user input and uses the classes in libuber to do so. I hope this puzzels you as
much as it puzzeled me. Rember how I wrote test cases for each library? Well I
had test cases for libuber and libtransport and have debugged them with
valgrind. However when I ran the cli, uber, I got 21000 valgrind errors.
Strange because they were all from within libuber and libtransport. Even
stranger still they were repeated twice. For example the distructor was being
invoced once, because I only had one instance, but valgrind would complain
twice that I was checking if a value was NULL before deleting it. Hmmm strange.
I would love to keep you in suspense but here you go I'll tell you what the
issue was. After spending 5+ hours debugging the issues valgrind was telling me
I had, I eventually deleted everying in the cli and still saw weird issues with
`main() { return 0; }`. Finally I turned my attention towards the makefile. I
had set the `-static` compile flag, which of course, had not been set in the
other libs makefiles. Removing that flag made all 21000 errors disapear, how
conveniant. If you ever compile staticly I beg you to remember this.
