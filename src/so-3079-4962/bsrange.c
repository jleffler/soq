/* SO 4584-8084 */

/* Determine if a range is contained within a set of ranges */

/*
** I have a set of ranges within an array.  For example (but note that
** my set of ranges will be larger than this):
**
**      static const Section arr[] = {
**          { .start_addr =   0, .length = 100, },
**          { .start_addr = 150, .length =  25, },
**          { .start_addr = 175, .length =  25, },
**          ...
**      };
**
** I then want to query whether another range would be contained within
** the union of all of these ranges via a function such as:
**
**      bool isEncapsulated(uint64_t addr, size_t len)
**      {
**          // Here I need some sort of algorithm to determine whether
**          // it is fully encapsulated.
**      }
**
** The primary difficulty I'm having is finding a way to account for the
** fact that the range provided may fall over the boundary of two
** defined ranges. eg. if start_addr = 170, length = 10 where it falls
** over the boundary of two of the defined ranges.
**
** Is there an elegant way of achieving this?
*/

/*
** Observations:
** Is the data in arr reliably sorted by start address, or merely
** coincidentally sorted in the sample data?  Do any of the ranges in
** the data overlap, or are they all disjoint, even though some ranges
** are adjacent?  Again, the sample data hints at "all disjoint", but it
** could be misleading.  And are the types integer types so we don't
** have to deal with floating point issues?  The answers to these
** questions critically affect the possible algorithms.
**
** Also, if the data isn't conveniently organized, then you should
** determine how often you'll be searching and decide whether it is
** worth the effort to preprocess the array into a sorted array of
** disjoint, non-contiguous intervals, so the search becomes easy —
** find the largest start less than equal to the one being searched for
** (binary search) and check that it covers the entire interval.  You
** might note the smallest start and largest end addresses, and the
** biggest size.  If your candidate interval is too big or falls outside
** the range of possibly valid addresses, you can eliminate it quickly.
*/

/*
** So, we need to be able to build an array of combined, sorted,
** disjoint, non-contigous ranges.  And we need a modified binary search
** that looks for the largest start address less than or equal to the
** target.
*/

#include "stderr.h"
#include <assert.h>
#include <inttypes.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct Section
{
    uintptr_t   start_addr;
    size_t      length;
} Section;

typedef struct SectionList
{
    size_t      num_sections;
    size_t      max_sections;
    Section   **sections;
} SectionList;

static const char *fmt_section(char *buffer, size_t buflen, const Section *section)
{
    snprintf(buffer, buflen, "(0x%.12" PRIXPTR ", %6zu)",
             section->start_addr, section->length);
    return buffer;
}

static void chk_sectionlist(const SectionList *list)
{
    if (list->num_sections > 1)
    {
        for (size_t i = 0; i < list->num_sections - 1; i++)
        {
            char buffer1[32];
            char buffer2[32];
            if (list->sections[i]->start_addr >= list->sections[i+1]->start_addr)
                err_error("Sections out of order: %zu: %s vs %zu: %s\n",
                        i+0, fmt_section(buffer1, sizeof(buffer1), list->sections[i+0]),
                        i+1, fmt_section(buffer2, sizeof(buffer2), list->sections[i+1]));
            else if (list->sections[i]->start_addr + list->sections[i]->length > list->sections[i+1]->start_addr)
                err_error("Sections are not disjoint and non-contiguous: %zu %s overlaps %zu: %s\n",
                        i+0, fmt_section(buffer1, sizeof(buffer1), list->sections[i+0]),
                        i+1, fmt_section(buffer2, sizeof(buffer2), list->sections[i+1]));
            else if (list->sections[i]->start_addr + list->sections[i]->length == list->sections[i+1]->start_addr)
                err_error("Sections are not disjoint and non-contiguous: %zu %s touches %zu: %s\n",
                        i+0, fmt_section(buffer1, sizeof(buffer1), list->sections[i+0]),
                        i+1, fmt_section(buffer2, sizeof(buffer2), list->sections[i+1]));
        }
    }
}

static void prt_sectionlist(const char *tag, const SectionList *list)
{
    printf("%s (%zu out of %zu):\n", tag, list->num_sections, list->max_sections);
    char buffer[32];
    for (size_t i = 0; i < list->num_sections; i++)
        printf("%2zu: %s\n", i, fmt_section(buffer, sizeof(buffer), list->sections[i]));
}

static void add_section(SectionList *list, Section section)
{
    assert(list != 0);
    assert(section.length != 0);
    if (!isEncapsulated(list, section))
    {
        /*
        ** Must add the section — but it may extend an existing
        ** section (before or after), or even connect two currently
        ** adjacent but non-contiguous sections.  Or it may simply need
        ** to be inserted before or after some existing section.
        */
    }
}

/* Not as efficient as all that - linear search */
static bool isEncapsulated(const SectionList *list, Section section)
{
    uintptr_t sect_start = section.start_addr;
    uintptr_t sect_end   = sect_start + section.length;
    for (size_t i = 0; i < list->num_sections; i++)
    {
        uintptr_t addr_start = list->sections[i]->start_addr;
        uintptr_t addr_end = addr_start + list->sections[i]->length;
        if (sect_start >= addr_start && sect_end <= addr_end)
            return true;
        if (sect_end < addr_start)
            return false;
    }
    return false;
}

static bool read_section(FILE *fp, Section *section)
{
    return(fscanf(fp, "%" SCNiPTR " %zu", &section->start_addr, &section->length) == 2);
}

int main(void)
{
    Section section;
    SectionList list = { 0, 0, 0 };

    /* Read to sentinel row with length of zero */
    while (read_section(stdin, &section) && section.length != 0)
    {
        char buffer[32];
        add_section(&list, section);
        prt_sectionlist(fmt_section(buffer, sizeof(buffer), &section), &list);
        chk_sectionlist(&list);
    }

    while (read_section(stdin, &section))
    {
        char buffer[32];
        fmt_section(buffer, sizeof(buffer), &section);
        if (isEncapsulated(&list, section))
            printf("%s encapsulated\n", buffer);
        else
            printf("%s not encapsulated\n", buffer);
    }

    return 0;
}
