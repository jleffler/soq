#ifndef GENLIST_H_INCLUDED
#define GENLIST_H_INCLUDED

#include <stddef.h>         /* size_t */

typedef struct list list;

typedef void (*Apply)(const void *vp, void *thunk);

extern list *listCreate(size_t typeSize);
extern void listDestroy(list *lp);

extern void listPushHead(list *lp, void *val);
extern void listPushTail(list *lp, void *val);

extern void listApplyForward(const list *lp, Apply apply, void *thunk);
extern void listApplyReverse(const list *lp, Apply apply, void *thunk);

#endif /* GENLIST_H_INCLUDED */
