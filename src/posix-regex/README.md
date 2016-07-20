### POSIX Regex

Question from Ramarao C <dramaraopatients@gmail.com> sent to my Gmail.
The question arrived out of thin air - I assumed it was someone from SO
but subsequent emails suggested maybe not - about POSIX regular
expressions.

On further review, this is clearly a follow-up to SO 3843-9698, which
asked how to read the contents of a text file into a single string so
that the data can be parsed with POSIX regular expressions.

The data is in `jain.txt`.

The first offering was `jl-sed.sh`.
This finds more lines than the outline code in `1.c` (renamed to
`regex-1.c`) that arrived later - that limits it to lines containing
`[stack]` too.

The code in `regex-1.c` has some obvious issues, but they're also
relatively minor issues.
A decent attempt was made.

The code in `regex-2.c` is the compressed and enhanced code.
The differences are more cosmetic than substantive, though.
