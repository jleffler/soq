#ifndef SO_STDERR_H_INCLUDED
#define SO_STDERR_H_INCLUDED

extern void err_error(const char *fmt, ...);
extern void err_setarg0(const char *arg0);
extern void err_syserr(const char *fmt, ...);
extern void err_usage(const char *usestr);

#endif /* SO_STDERR_H_INCLUDED */
