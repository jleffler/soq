#include<stdio.h>
#include<string.h>

#define STRINGSIZE 64
void main()
{
    char *line1 = NULL;
    char *line2 = NULL;

    size_t size1;
    size_t size2;

    getline(&line1, &size1, stdin);
    getline(&line2, &size2, stdin);

    char*  spilted1 = strtok(line1, " ");

    while (spilted1 != NULL){
        if (strstr(line2, spilted1) == NULL){
            printf("%s", spilted1);
        }
        spilted1 = strtok(NULL, " ");
    }

}

/*
Initialize size1 and size2 to zero too for safety.  You'll need two
arrays of char pointers, one for each line of input.  You'll split the
first line into the first array, and the second line into the second
array.  Then you'll go through the two arrays of pointers, comparing
strings and counting only those that do not match any of the entries in
the other array.  (What do you do if one input line itself contains
repeats — The Lion, the Witch, and the Wardrobe for example?  Also, do
you need to treat The as the same as the in that example?)

You can use strtok_r() or strtok_s() if you have them available; at a
pinch, you could use strtok(), but it is dangerous to use that in
library code.  And you'll need to use strcmp() to compare the strings
— plus macros/functions from <ctype.h> to handle case-conversion if
that's appropriate.

Also note that strtok() is destructive.  If you've split string 1 with
it, you can't then search in string 1 when you split string 2.  Also
note that strstr("then came a deluge", "the") matches, even though most
people would not regard the haystack string as containing the needle
word the.
*/
