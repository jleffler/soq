SO 7297-3891 - Find file descriptor of directory associated with filename
https://stackoverflow.com/questions/72973891

This question, SO 7297-3891, was related to SO 7290-5567
(https://stackoverflow.com/questions/72973891) and was asked a few days
later.

The code shows using `futimensat()` with `AT_FDCWD` to set the times on files named
on the command line.

* `ft59.c`

This is an upgraded version of the code shown in the answer to the question.

* `ft97.c`

This is the code shown in the answer to the question.  It sets the modification and
access time to the same value.

Note that you need a command capable of showing nanosecond timestamps to see that it
is working.

* When compiled with the appropriate options, the JLSS command `fl`
  (file lister) can do the job.
* The macOS `stat` command does not appear to suport sub-second
  timestamps.  The man page mentions usingf the `st_atime`, `st_mtime`,
  `st_ctime` fields, which are of type `time_t`.
* The GNU `stat` command from the coreutils package does support
  sub-second times.

