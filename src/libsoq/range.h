/*
@(#)File:           range.h
@(#)Purpose:        Declaration of range parsing functions
@(#)Author:         J Leffler
@(#)Copyright:      (C) JLSS 1997,2005,2007-08,2015
@(#)Derivation:     range.h 1.11 2015/06/19 06:51:43
*/

/*TABSTOP=4*/

#ifndef RANGE_H
#define RANGE_H

/*
** parse_range(): parse range of non-negative numbers.
** Source: range.c
**
** Given a string, parse_range() returns the lo and hi values corresponding
** to the range specified by the string.  For example:
**      Input:          Low             High
**      23              23              23
**      23-25           23              25
**      23-             23              0
**      -23             0               23
** Any delimiter other than '-' before or after a number terminates the
** scan, but commas are skipped.  Returns pointer to character after
** last character parsed (which may or may not be '\0') if successful.
** If there is no conversion, returns a pointer to the string.
** Otherwise, it returns null indicating there is nothing more to parse.
**
** Idiomatic use:
**
**  long lo, hi;
**  const char *ptr = source_string;
**  const char *nxt;
**  while ((nxt = parse_range(ptr, &lo, &hi)) != 0)
**  {
**      if (nxt == ptr)
**          err_error("invalid range string (%s)\n", source_string);
**      use_range(lo, hi);
**      ptr = nxt;
**  }
*/
extern const char *parse_range(const char *str, long *lo, long *hi);

/* Set conversion base, returning old value. Default: 10 */
/* Conversion bases 0, 2, 8, 10, 16 sane; 0, 2-36 valid. */
extern int parse_setbase(int new_base);

/*
** numeric_range(): parse range of numbers, positive or negative.
** Source: range2.c
**
**  Input:      Low     High
**  23          23      23
**  -23        -23     -23
**  23:25       23      25
**  23..25      23      25
**  -23..-25   -25     -23
**  -23..25    -23      25
**  23..-25    -25      23
**
** Any delimiter other than '+' or '-' before or after a number
** terminates the scan, but commas are skipped.  Returns pointer to
** character after last character parsed (which may or may not be '\0')
** if successful.  If there is no conversion, return a pointer to the
** string.  Otherwise, return null indicating there is nothing to parse.
**
** Idiomatic use:
**
**  long lo, hi;
**  const char *ptr = source_string;
**  const char *nxt;
**  while ((nxt = numeric_range(ptr, &lo, &hi)) != 0)
**  {
**      if (nxt == ptr)
**          err_error("invalid range string (%s)\n", source_string);
**      use_range(lo, hi);
**      ptr = nxt;
**  }
*/
extern const char *numeric_range(const char *str, long *lo, long *hi);

/* Set conversion base, returning old value. Default: 10 */
/* Conversion bases 0, 2, 8, 10, 16 sane; 0, 2-36 valid. */
extern int numeric_setbase(int new_base);

/*
** double_range():
**      parse multiple ranges of floating-point numbers.
**
** Source: range3.c
**
**  Input:       Low    High
**  23            23      23
**  -23          -23     -23
**  23:25         23      25
**  23.0..25      23      25
**  -23.0..-25   -25     -23
**  -23.0..25    -23      25
**  23.0..-25    -25      23
**
**  If conversion is OK, returns non-null pointer to start of next
**  number, or to '\0' at end of string, sets *lo and *hi, and
**  guarantees *lo <= *hi.  If conversion is invalid, returns pointer to
**  start of string.  Otherwise, it returns null indicating there is no
**  more string to parse.
**
** Idiomatic use:
**
**  double lo, hi;
**  const char *ptr = source_string;
**  const char *nxt;
**  while ((nxt = double_range(ptr, &lo, &hi)) != 0)
**  {
**      if (nxt == ptr)
**          err_error("invalid range string (%s)\n", source_string);
**      use_range(lo, hi);
**      ptr = nxt;
**  }
*/
extern const char *double_range(const char *str, double *lo, double *hi);

#endif /* RANGE_H */
