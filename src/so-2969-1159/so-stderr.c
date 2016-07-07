#include "so-stderr.h"
#include <errno.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static const char *argv0 = "**undefined**";

void err_setarg0(const char *arg0)
{
  argv0 = arg0;
}

void err_usage(const char *usestr)
{
  fprintf(stderr, "Usage: %s %s\n", argv0, usestr);
  exit(EXIT_FAILURE);
}

void err_error(const char *fmt, ...)
{
  fprintf(stderr, "%s: ", argv0);
  va_list args;
  va_start(args, fmt);
  vfprintf(stderr, fmt, args);
  va_end(args);
  exit(EXIT_FAILURE);
}

void err_syserr(const char *fmt, ...)
{
  int errnum = errno;
  fprintf(stderr, "%s: ", argv0);
  va_list args;
  va_start(args, fmt);
  vfprintf(stderr, fmt, args);
  va_end(args);
  if (errnum != 0)
    fprintf(stderr, "(%d: %s)", errnum, strerror(errnum));
  putc('\n', stderr);
  exit(EXIT_FAILURE);
}
