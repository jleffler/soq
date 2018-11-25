/* Derived from code in SO 1886-3184 */
/* Original answer by https://stackoverflow.com/users/703016/kretab-chabawenizc */
#ifndef MEMPROBE_H_INCLUDED
#define MEMPROBE_H_INCLUDED

#include <stddef.h>
extern int probe_memory_ro(const void *address, size_t length);
extern int probe_memory_rw(void *address, size_t length);
extern void probe_finish(void);
extern int probe_init(void);

#endif /* MEMPROBE_H_INCLUDED */
