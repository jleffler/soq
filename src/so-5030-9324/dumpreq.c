#include "request.h"
#include <stdio.h>

void dump_request(const char *tag, const struct request *rp)
{
    printf("%s:\n", tag);
    printf("- PID requesting seats: %d\n", rp->pid);
    printf("- Number of seats wanted: %d\n", rp->num_wanted_seats);
    printf("- Number of seats in preferred list: %d\n", rp->pref_seats_size);
    for (int i = 0; i < rp->pref_seats_size; i++)
        printf("  %d is seat %d\n", i, rp->pref_seat_list[i]);
    fflush(stdout);
}
