#ifndef OSFILE_H_INCLUDED
#define OSFILE_H_INCLUDED

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

extern FILE *ifx_fp_close(FILE *fp);
extern int   ifx_fd_close(int   fd);

#endif /* OSFILE_H_INCLUDED */

