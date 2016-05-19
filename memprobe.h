#ifndef MEMPROBE_H_INCLUDED
#define MEMPROBE_H_INCLUDED

#include <stddef.h>
extern int probe_memory_rd(const void *address, size_t length);
extern int probe_memory_rw(void *address, size_t length);
extern void probe_finish(void);
extern int probe_init(void);

#endif /* MEMPROBE_H_INCLUDED */
