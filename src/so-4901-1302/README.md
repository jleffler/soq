### Stack Overflow Question 4901-1302

[SO 4901-1302](https://stackoverflow.com/q/49011302) &mdash;
How to convert from fopen to open function?

### Code using file stream

In the `cache_reader.c` file:

    void cr_close(cr_file *f)
    {
        free(f->buffer);
        fclose(f->file);
    }

    cr_file *cr_open(char *filename, int buffersize)
    {
        FILE *f;
        if ((f = fopen(filename, "r")) == NULL)
        {
            fprintf(stderr, "Cannot open %s\n", filename);
            return 0;
        }

        cr_file *a = (cr_file *)malloc(sizeof(cr_file));
        a->file = f;
        a->bufferlength = buffersize;
        a->usedbuffer = buffersize;
        a->buffer = (char *)malloc(sizeof(char) * buffersize);
        refill(a);
        return a;
    }

In the `cache_reader.h` file:

    typedef struct
    {
        FILE *file;       // File being read
        int bufferlength; // Fixed buffer length
        int usedbuffer;   // Current point in the buffer
        char *buffer;     // A pointer to a piece of memory
        //  same length as "bufferlength"
    } cr_file;
    // Open a file with a given size of buffer to cache with
    cr_file *cr_open(char *filename, int buffersize);

    // Close an open file
    void cr_close(cr_file *f);
    int refill(cr_file *buff);

In the `cache_example.c` file:

    int main()
    {
        char c;

        // Open a file
        cr_file *f = cr_open("text", 20);

        // While there are useful bytes coming from it
        while ((c = cr_read_byte(f)) != EOF)
            // Print them
            printf("%c", c);

        // Then close the file
        cr_close(f);

        // And finish
        return 0;
    }

### Answer

<sup>From comments</sup>

The object of the exercise is to leave the example code unchanged, but
reimplement the other code to use file descriptors instead of file
streams.
Sadly, the header exposes the internals of the structure, unnecessarily,
so the example needs to be recompiled.
You will change the `FILE *` member to an `int`.
You will not use any function that takes a file stream argument.

The header (`cache_reader.h`) should contain this (and not the structure
definition):

    typedef struct cr_file cr_file;

The source (`cache_reader.c`) should contain:

    struct cr_file
    {
        int file;
        int bufferlength;
        int usedbuffer;
        char *buffer;
    };

This gives you an opaque type in the client (example) code, and allows
you to change the structure without needing to recompile the client code
(though you would have to recompile the implementation, of course — we
can't work complete miracles).

Of course you can make your clients recompile their code whenever you
make changes to the internals of the library.
However, it is often more convenient in the long run if you can make
changes and improvements to your library code without requiring the
consumers (other programmers) to recompile their code.
Binary compatibility is very important for big libraries, like the
standard C library on a given platform.
For a tiny project like this, it doesn't matter — but you'll need to
learn about the larger scale issue too, at least in due course, if you
stick with programming as a career.

### Reworked code

Note that I concluded I needed some different members to support your
use case — I needed to know the size of the allocated buffer, the
amount of data actually in the buffer, and the current position for
reading.
I renamed the members to `bufmax` (your `bufferlength`), `bufpos` (your
`usedbuffer`), and added `buflen`.

I wrote sample code for `cr_read_byte()`, and it works reading a file.

However, there is considerable work to be done to support writing too,
and moving around in the file other than one byte at a time, and so on.

