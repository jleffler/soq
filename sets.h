/* SO 31096894 - sets.h */

#ifndef SETS_H_INCLUDED
#define SETS_H_INCLUDED

typedef struct Set Set;
enum { MAX_ELEMENTS = 1024 };

extern Set *create(void);
extern void destroy(Set *set);
extern void insert(Set *set, int value);
extern void delete(Set *set, int value);
extern int in_set(Set *set, int value);

#endif /* SETS_H_INCLUDED */
