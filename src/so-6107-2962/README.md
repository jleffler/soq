SO 6107-2962 Identifying the header file in a C program

> I am trying to compile a C program found at this link (based on a
> scientific publication):

> https://static-content.springer.com/esm/art%3A10.1038%2Fncomms11219/MediaObjects/41467_2016_BFncomms11219_MOESM262_ESM.txt

The basic question was easily answered.
There was a line `#include "polygyny14.h"` near the top, and a long way
down the file a comment saying `polygyny14.h`.

The file, when downloaded, is mostly in a Mac format with CR line
endings:

    41467_2016_BFncomms11219_MOESM262_ESM.txt: 2 Unix, 3485 Mac, 1 DOS

The file was converted to Unix line ending (`ule -u`), and eventually
cleaned of trailing white space on lines, and trailing garbage was
removed.
This 'original' code is saved as `polygyny14.txt`.

The files `polygyny14.h` and `polygyny14.c` were separately cleaned up.

The structure is unusual — there are functions defined in the header.
These were made static, and then a number of them were identified as not
being used.
Initially the functions were enclosed in `#ifdef
DEFINE_UNUSED_FUNCTIONS` / `#endif` markers.
They were subsequently deleted.
There were a lot variables that were either wholly unused, or only set
but otherwise unused; these were deleted.
The 'use' was usually just initializing the variable to 0.

The change that was sought &mdash; the original trigger for cleaning up
&mdash; was to clean up a set of 50 `FILE *` variables, each writing to
a separate file, all with systematic names.
Cleaning this part up removed over 200 lines and added less than 40.

The header really isn't necessary — there is only one source file that
it is 'sharing' information with.
