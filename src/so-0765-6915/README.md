### Stack Overflow Question 0765-6915

[SO 0765-6915](https://stackoverflow.com/q/07656915) &mdash;

Sorting and merging multiple files of integers in a binary format.

Each file contains 4-byte integers in native byte order (written by
`fwrite()`, in other words).
Each file is sorted in memory by a separate process, then the sorted
results are piped to merging processes, which end up reporting to the
start process.

There isn't a data generation mechanism here, which is some sort of
oversight.
Let's see: what would be needed?

Command line data generator taking options:

* number of files to generate (default 2)
* seed to use (optional — default is 4 bytes from `/dev/urandom`)
* report seed (for repeatability)
* range for number of entries in each file (default: 100)
* range for the values found in each file (default range of `int`)
* file name format string (requires a `%d` in it)
* start number for file numbers (default 0)

Uses the `Xrand48()` series of functions to generate the values.

Nice simple job, especially with `range.h` and related files already in
`libsoq` to handle ranges.

