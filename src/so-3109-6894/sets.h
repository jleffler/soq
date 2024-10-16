/* SO 3109-6894 - sets.h */

/* Set of elements 1..1024 - in C89/C90 */
#ifndef SETS_H_INCLUDED
#define SETS_H_INCLUDED

typedef struct Set Set;
enum { MAX_ELEMENTS = 1024 };

extern Set *set_create(void);
extern void set_destroy(Set *set);
extern void set_insert(Set *set, int value);
extern void set_delete(Set *set, int value);
extern int  set_member(Set *set, int value);
extern void set_difference(const Set *set1, const Set *set2, Set *result);
extern void set_union(const Set *set1, const Set *set2, Set *result);
extern void set_intersect(const Set *set1, const Set *set2, Set *result);
extern void set_empty(Set *set);

#endif /* SETS_H_INCLUDED */
