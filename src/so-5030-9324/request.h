#ifndef REQUEST_H_INCLUDED
#define REQUEST_H_INCLUDED

#define FIFO_NAME "seat-request.fifo"

struct request
{
    int pid;
    int num_wanted_seats;
    int pref_seats_size;
    int pref_seat_list[];
};

extern void dump_request(const char *tag, const struct request *rp);

#endif /* REQUEST_H_INCLUDED */

