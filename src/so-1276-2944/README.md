### Refactoring of ghastly code

The code in megamat1.c is basically what was in the questions, fixed so
it runs.

The code in megamat2.c refactors the expression code in megamat1.c so
that it is much simpler to understand.

### How this code got here?

The branch so/12762944 stripped out all except these files.  As such, it
is practically unmergeable.  So, the material from the branch was copied
into the so-1276-2944 directory and then the branch sphinx/reorg.003
added the files.

There might be a better way to do it, but given the anti-Git methods
used on the branch, maybe not.
