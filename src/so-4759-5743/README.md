### Stack Overflow Question 4759-5743

[SO 4759-5743](https://stackoverflow.com/q/47595743) &mdash;
Creating a new process when a process dies

The original code in the question was a very rudimentary but not wholly
unworkable piece of code for maintaining a list of N processes at work
as the individual processes die.

The first checkin of mon61.c on this branch gives the posted answer.

As noted, there were issues with 'unknown PID' messages.
On further scrutiny, those messages are from children that died from a
signal.
They did exist; they weren't recorded as auccessful.
Subsequent check-ins will endeavour to fix this issue.

