Debugging Study Program
---

For this program I didnt have any reason to use GDB. So as per my usual
workflow I stuck with valgrind and clang-analyser.

Clang found a bug where I was hidding the virtual function of the parent.
```
hides overloaded virtual function
...
declared here: different qualifiers (const vs none)
```
I thought this was interesting because it worked when I compiled with gcc. I
had just forgotten to put the const keyword.

When I made the 2-3 tree I was making a node class then was going to make a
parent class, as I had done with every other data structure I've written.
However as I closed in on finishing writing the node I realized that the node
and the tree were one and the same! So I avoided writing a tree class. The flip
side of this is that the destructor for the node frees the memory it is
managing. It does not delete the whole tree. Looking back on it I should have
added some setting that would enable that but I didn't. For my test cases I
started with a small number, 2, but then when I changed it to adding 100 nodes
I had a memory leak! It took me a while to realize that I needed to call the
`remove_all` method.

I had a bug that I felt very ashamed come up in valgrind. It was a seg fault
from within the string class I had made weeks ago! And I thought I had tested
it throughly but apperently not. Valgrind is great because it tells you the
offending line and stacktrace for where the program seg faulted. It was easy
for me to see that I had passed posibly NULL strings to `strcmp`, with
desastorous effect. The fix was a simple wrapper on `strcmp` to also check that
the pointers are not NULL.

I did not have time to write that many test cases this time. Which is sad but
oh well. I think that test driven development is very important, I set up a CI
server at my house a while ago and because I build with clang to use scan-build
on my laptop I sometimes have builds that fail when built with gcc, clang seems
to be nicer about including libs for you. The CI server helps me catch those
bugs by texting me when the builds fail.
