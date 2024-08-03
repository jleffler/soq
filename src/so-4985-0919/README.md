### Stack Overflow Question 4985-0919

[SO 4985-0919](https://stackoverflow.com/q/49850919) &mdash;
Get names of cities of customers who have placed an order through employees who have sold

It's a sufficiently complex query that I'd solve it using what I call
'Test-Driven Query Design' or TDQD.  Here are two sequences of queries
that lead to the same plausible answer — the expected output is not
given in the question, which makes it hard to be sure the query has been
analyzed accurately.

The requirement is stated as:

* Query: Get names of cities of customers who have placed an order
  through employees who have sold the book "Quickbooks for Business".
* Required: you must complete this query with sub-select.

It's possible to interpret the 'with sub-select' requirement to mean 'at
least one sub-query' or 'only using sub-queries'.  There are two parts
to this answer — the first assuming a single sub-query is sufficient,
and the second assuming that only sub-queries may be used.

I regard TDQD as a good way of learning how to build big queries from a
number of small queries that you have demonstrated work (because you
tested the small queries).

# One sub-query is sufficient

### TDQD Step A1 — Employees who have sold the book 'Quickbooks for Business'

This is a fairly big first step; it can be broken down into smaller
queries to build up the output list of employee numbers if you're not
familiar with writing queries.

    SELECT e.eno
      FROM employee AS e
      JOIN salesorder AS o ON o.eno = e.eno
      JOIN orderline AS l ON o.ono = l.ono
      JOIN book AS b ON l.bno = b.bno
     WHERE b.bname = 'Quickbooks for Business';

Output:

    P0239401
    P0239402

_Simplification:_ The query doesn't need to include the `employee`
table; the employee numbers are in the `salesOrder` table:

    SELECT o.eno
      FROM salesorder AS o
      JOIN orderline AS l ON o.ono = l.ono
      JOIN book AS b ON l.bno = b.bno
     WHERE b.bname = 'Quickbooks for Business';

This gives the same result.  The change can be propagated through the
all the queries.  Note that the second part of the answer (the 'all
sub-queries' variant) does not select from the `employee` table at all,
either.  That asymmetry should have tipped me off earlier, but I didn't
spot it.  And the chances are that if I'd built up this first step in
the TDQD sequence with smaller steps, I wouldn't have made the mistake
here, either.

### TDQD Step A2 — Customers who have placed an order from a list of employees

    SELECT c.cno
      FROM customer AS c
      JOIN salesorder AS o ON c.cno = o.cno
     WHERE o.eno IN
           (SELECT e.eno
              FROM employee AS e
              JOIN salesorder AS o ON o.eno = e.eno
              JOIN orderline AS l ON o.ono = l.ono
              JOIN book AS b ON l.bno = b.bno
             WHERE b.bname = 'Quickbooks for Business'
           );

This gives you the mandatory sub-query.

Output:

    23513
    23511
    23513
    23511
    23512
    23513

This is an intermediate result; there's no need to remove duplicates or
order this result.

_Simplification:_

    SELECT c.cno
      FROM customer AS c
      JOIN salesorder AS o ON c.cno = o.cno
     WHERE o.eno IN
           (SELECT o.eno
              FROM salesorder AS o
              JOIN orderline AS l ON o.ono = l.ono
              JOIN book AS b ON l.bno = b.bno
             WHERE b.bname = 'Quickbooks for Business'
           );

### TDQD Step A3 — Cities of customers who have placed an order from a list of employees

    SELECT DISTINCT z.city
      FROM customer   AS c
      JOIN salesorder AS o ON c.cno = o.cno
      JOIN zipcode    AS z ON z.zip = c.zip
     WHERE o.eno IN
           (SELECT e.eno
              FROM employee   AS e
              JOIN salesorder AS o ON o.eno = e.eno
              JOIN orderline  AS l ON o.ono = l.ono
              JOIN book       AS b ON l.bno = b.bno
             WHERE b.bname = 'Quickbooks for Business'
           )
     ORDER BY z.city;

Output:

    Bellingham
    San Jose

_Simplification:_

    SELECT DISTINCT z.city
      FROM customer AS c
      JOIN salesorder AS o ON c.cno = o.cno
      JOIN zipcode AS z ON z.zip = c.zip
     WHERE o.eno IN
           (SELECT o.eno
              FROM salesorder AS o
              JOIN orderline AS l ON o.ono = l.ono
              JOIN book AS b ON l.bno = b.bno
             WHERE b.bname = 'Quickbooks for Business'
           )
     ORDER BY z.city;

### TDQD Step A4 — Do not use a sub-query

The assignment requires the sub-query, but the real world doesn't.
However, the SalesOrder table has to figure twice in the query, so it
gets aliased to `o1` and `o2`:

 -- TDQD Step 4
-- Do not use a sub-query

    SELECT DISTINCT z.city
      FROM customer   AS c
      JOIN salesorder AS o1 ON c.cno  = o1.cno
      JOIN zipcode    AS z  ON c.zip  = z.zip
      JOIN employee   AS e  ON o1.eno = e.eno
      JOIN salesorder AS o2 ON o2.eno = e.eno
      JOIN orderline  AS l  ON o2.ono = l.ono
      JOIN book       AS b  ON l.bno  = b.bno
     WHERE b.bname = 'Quickbooks for Business'
     ORDER BY z.city;

Output:

    Bellingham
    San Jose

_Simplification:_

    SELECT DISTINCT z.city
      FROM customer   AS c
      JOIN salesorder AS o1 ON c.cno  = o1.cno
      JOIN zipcode    AS z  ON z.zip  = c.zip
      JOIN salesorder AS o2 ON o2.eno = o1.eno
      JOIN orderline  AS l  ON o2.ono = l.ono
      JOIN book       AS b  ON l.bno  = b.bno
     WHERE b.bname = 'Quickbooks for Business'
     ORDER BY z.city;

# Only sub-queries may be used

If the assumption that a single sub-query is sufficient is wrong and in
fact only sub-queries may be used, then an alternative TDQD sequence
follows.

### TDQD Step B1 — Book number of 'Quickbooks for Business' (QfB)

    SELECT b.bno
      FROM book AS b
     WHERE b.bname = 'Quickbooks for Business';

Output:

    10605

### TDQD Step B2 — Order numbers for orders including QfB

    SELECT l.ono
      FROM orderline AS l
     WHERE l.bno IN
           (SELECT b.bno
              FROM book AS b
             WHERE b.bname = 'Quickbooks for Business'
           );

Output:

    1021
    1022

### TDQD Step B3 — Employee numbers for orders including QfB

    SELECT DISTINCT o1.eno
      FROM salesorder AS o1
     WHERE o1.ono IN
           (SELECT l.ono
              FROM orderline AS l
             WHERE l.bno IN
                   (SELECT b.bno
                      FROM book AS b
                     WHERE b.bname = 'Quickbooks for Business'
                   )
           );

Output:

    P0239401
    P0239402

### TDQD Step B4 — Customer numbers who placed an orders through employees in list

    SELECT DISTINCT o2.cno
      FROM salesorder AS o2
     WHERE o2.eno IN
           (SELECT o1.eno
              FROM salesorder AS o1
             WHERE o1.ono IN
                   (SELECT l.ono
                      FROM orderline AS l
                     WHERE l.bno IN
                           (SELECT b.bno
                              FROM book AS b
                             WHERE b.bname = 'Quickbooks for Business'
                           )
                   )
           );

Output:

    23511
    23512
    23513

### TDQD Step B5 — Zip codes of customers who placed orders through employees in list

    SELECT DISTINCT c.zip
      FROM customer AS c
     WHERE c.cno IN
           (SELECT o2.cno
              FROM salesorder AS o2
             WHERE o2.eno IN
                   (SELECT o1.eno
                      FROM salesorder AS o1
                     WHERE o1.ono IN
                           (SELECT l.ono
                              FROM orderline AS l
                             WHERE l.bno IN
                                   (SELECT b.bno
                                      FROM book AS b
                                     WHERE b.bname = 'Quickbooks for Business'
                                   )
                           )
                   )
           );

Output:

    95124
    98225

### TDQD Step B6 — Cities of customers who placed orders through employees in list

    SELECT DISTINCT z.city
      FROM zipcode AS z
     WHERE z.zip IN
           (SELECT DISTINCT c.zip
              FROM customer AS c
             WHERE c.cno IN
                   (SELECT o2.cno
                      FROM salesorder AS o2
                     WHERE o2.eno IN
                           (SELECT o1.eno
                              FROM salesorder AS o1
                             WHERE o1.ono IN
                                   (SELECT l.ono
                                      FROM orderline AS l
                                     WHERE l.bno IN
                                           (SELECT b.bno
                                              FROM book AS b
                                             WHERE b.bname = 'Quickbooks for Business'
                                           )
                                   )
                           )
                   )
           );

Output:

    Bellingham
    San Jose

Fortunately, the same output is generated for both final queries.
This lends us some reassurance that the queries are equivalent.

