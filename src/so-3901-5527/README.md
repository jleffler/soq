# [SO 3901-5527](https://stackoverflow.com/q/39015527) &mdash; Is it safe to rename files while using readdir?

A simple question couched in terms of Perl rather than C.

# Initial answer

My initial answer was:

<hr>

The underlying system call is POSIX's
[`readdir()`](http://pubs.opengroup.org/onlinepubs/9699919799/functions/readdir.html),
and the specification says:

> If a file is removed from or added to the directory after the most
> recent call to `opendir()` or `rewinddir()`, whether a subsequent call
> to `readdir()` returns an entry for that file is unspecified.

It simply means that you might or might not get to see the files.
You might find that a particular platform does specify what happens, but
it probably isn't portable to other systems.

<hr>

# Revised answer

### Answer

The underlying system call is POSIX's
[`readdir()`](http://pubs.opengroup.org/onlinepubs/9699919799/functions/readdir.html),
and the specification says:

> If a file is removed from or added to the directory after the most
> recent call to `opendir()` or `rewinddir()`, whether a subsequent call
> to `readdir()` returns an entry for that file is unspecified.

It simply means that you might or might not get to see the files.
You might find that a particular platform does specify what happens, but
it probably isn't portable to other systems.

<hr>

### Demonstration

[ikegami](https://stackoverflow.com/users/589924/ikegami)
[asked](https://stackoverflow.com/questions/39015527/is-it-safe-to-rename-files-while-using-readdir/39017355?noredirect=1#comment65400149_39017355):

> `rename` neither adds nor removes any directory entries, though.
> It just edits one.

I [responded]():

> It (`rename()`) changes an entry in the directory; what happens
> depends on how [the file system] is implemented.
> If you change the file name from `a` to
> `humongous-long-name-that-is-too-boring-to-be-believable`, there's a
> decent chance that the entry will move in the directory on disk,
> leading to unspecified behaviour [as noted in the main answer].
> … Whether … `rename()` actually screws up a scan with `readdir()`
> depends on the system (operating system and file system), which is all
> that I claimed.


After further discussion, I created this example of what can and does
happen on one specific system.
I used the steps:

* Create a directory — its name does not matter.
* Change into that directory.
* Copy `readdir.c` and `make.files.sh` into the directory.
* Create program `readdir` from source `readdir.c` (use `make readdir`, for example).
  - The code assumes that the `struct dirent` includes member `d_namlen` which is not mandated by POSIX.
  - It would be feasible to do without it (but minor changes would be needed).
* Create a file (or directory) `a`.
* Run `./readdir`.  Hit return when it prompts you.  You should see
  output similar to this, but the inode numbers will be different.

        $ ./readdir
        44249044: (  1) .
        42581443: (  2) ..
        44257388: (  1) a
        Found entry 'a' - hit return to continue: 
        Continuing...
        44256100: ( 13) make.files.sh
        44256074: (  8) makefile
        44250423: (  7) readdir
        44255988: (  9) readdir.c
        44250424: ( 12) readdir.dSYM
        $

* Run `sh make.files.sh`.  This will create files `moderately-long-file-name.000` .. `moderately-long-file-name.999`.
* Run `./readdir` again. Do not hit return yet.
* Switch to a different terminal window.
* Change directory to the one where the test is being run.
* Run: `mv a  zzz-let-sleeping-file-renames-lie-unperturbed`
* Switch back to the terminal window running `readdir`.
* Hit return.  You will probably see output similar to:

        $ ./readdir
        44249044: (  1) .
        42581443: (  2) ..
        44257388: (  1) a
        Found entry 'a' - hit return to continue: 
        Continuing...
        44256100: ( 13) make.files.sh
        44257524: ( 29) moderately-long-file-name.000
        44257525: ( 29) moderately-long-file-name.001
        44257526: ( 29) moderately-long-file-name.002
        ...
        44258521: ( 29) moderately-long-file-name.997
        44258522: ( 29) moderately-long-file-name.998
        44258523: ( 29) moderately-long-file-name.999
        44250423: (  7) readdir
        44255988: (  9) readdir.c
        44250424: ( 12) readdir.dSYM
        44257114: ( 45) zzz-let-sleeping-file-renames-lie-unperturbed
        $

This is what I got on Mac OS X 10.11.6 El Capitan with the default HFS+
file system.  When the directory was small (without the moderately long
file names), then the renamed file did not show up.  When the extra
files were created so that the directory size was around 34 KiB, then
the renamed file did show up.  Note that the inode number has changed.
(HFS+ is also interesting because the number of links to the directory
is the number of names in the directory — I was getting a link count
such as 1013 because there were some extra files lurking around.)

This demonstrates that on some file systems (specifically, Apple's HFS+)
and under some circumstances, the `readdir()` scan of a directory is
affected by a rename operation on a file.  If you wish to write and use
a `rename` command instead of using `mv`, so be it &mdash; when I tried,
it made no difference to the result.

# Conclusion

On other file systems or other operating systems, YMMV.  However, this
suffices to demonstrate that on some systems, renaming a file while a
`readdir()` scan is in progress can end up with the same 'file' appearing
twice in the output.

### `make.files.sh`

    #!/bin/sh

    for file in $(seq -f 'moderately-long-file-name.%03.0f' 0 999)
    do > "$file"
    done

### `readdir.c`

    /* SO 3901-5527 - attempt to demonstrate renaming moving entries */
    #include <dirent.h>
    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include <unistd.h>

    static const char *stop_after = "a";

    static void process_directory(const char *dirname)
    {
        DIR *dp = opendir(dirname);

        if (dp == 0)
            fprintf(stderr, "Failed to open directory %s\n", dirname);
        else
        {
            struct dirent *entry;
            while ((entry = readdir(dp)) != 0)
            {
                /* Ignore current and parent directory */
                printf("%8d: (%3d) %s\n", (int)entry->d_ino, entry->d_namlen, entry->d_name);
                if (strcmp(entry->d_name, stop_after) == 0)
                {
                    printf("Found entry '%s' - hit return to continue: ", stop_after);
                    fflush(stdout);
                    char *buffer = 0;
                    size_t buflen = 0;
                    getline(&buffer, &buflen, stdin);
                    free(buffer);
                    printf("Continuing...\n");
                }
            }
            closedir(dp);
        }
    }

    int main(int argc, char **argv)
    {
        int opt;
        while ((opt = getopt(argc, argv, "s:")) != -1)
        {
            switch (opt)
            {
            case 's':
                stop_after = optarg;
                break;;
            default:
                fprintf(stderr, "%s: Unrecognized option '-%c'\n", argv[0], optopt);
                fprintf(stderr, "Usage: %s [-s stop_after] [directory ...]\n", argv[0]);
                return(EXIT_FAILURE);
            }
        }
        if (optind == argc)
            process_directory(".");
        else
        {
            for (int i = optind; i < argc; i++)
                process_directory(argv[i]);
        }
        return(0);
    }

