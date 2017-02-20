### Stack Overflow Question 2969-1159

[SO 2969-1159](http://stackoverflow.com/q/29691159) &mdash;
Making a shared data structure in C

The program `shm-master` allows you to simulate the basic management
of a shared memory segment in most plausible sequences.

[SO 4225-8485](http://stackoverflow.com/q/42258485) &mdash;
Detaching from shared memory before removing it &mdash; asks about
whether you can delete a shared memory segment while programs are
using it.  Adding the `-t time` option to the code means that you
can run `shm-master` in background, having it sleep after it has
created or attached to a shared memory segment, and you can have
multiple `shm-master` processes connected to it at the same time.
