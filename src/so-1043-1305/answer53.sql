There are times when your goals of `1..COUNT(*)` numbering and 'do not
renumber locked rows' lead to irresolvable conflict.  For example:

    NAME  SEQ_NO    LOCKED
    Foo    1        N
    Bar   13        Y
    Abc   14        Y
    Baz    5        N
    Cde    7        N

I will assume that the required output for this scenario is:

    NAME  SEQ_NO    LOCKED
    Foo    1        N
    Baz    2        N
    Cde    3        N
    Bar   13        Y
    Abc   14        Y

You example shows the unlocked data being kept in its original sequence
number order, and the locked data obviously doesn't get a new number.

I assume that there are no duplicate sequence numbers in the original
data.

<hr>

### Quick Summary

It is an interesting and tricky problem.  The key to reordering the data
is knowing where to place the unlocked rows.  In the example data:

    NAME  OLD_SEQ   LOCKED   NEW_SEQ
    Foo   1         N        1
    Bar   3         Y        3
    Abc   4         Y        4
    Baz   5         N        2
    Cde   7         N        5

We can give the unlocked rows a sequence number counting from 1..3, so
we end up with pairs of _ord:old_ sequence **A { 1:1, 2:5, 3:7 }**.  We
can generate a list of slots for the result set 1..5.  We remove from
that list of slots those slots held by locked rows, leaving { 1, 2, 5 }
as the list of slots to be occupied by unlocked rows in the reordered
list.  We then number those in order too, leaving pairs _ord:new_ **B {
1:1, 2:2, 3:5 }**.  We can then join these two lists, A and B, on the
first field and project away the sequencing, to leave pairs of _new:old_
slot numbers **C { 1:1, 2:5, 5:7 }**.  The locked rows produce a set of
_new:old_ values where _new = old_ in each case, so **D { 3:3, 4:4 }**.
The final result is the union of C and D, so the result set contains:

* old sequence number 1 in new sequence number 1;
* old 5 in new 2;
* (old 3 in new 3);
* (old 4 in new 4); and
* old 7 in new 5.

This works for the case where the locked rows have sequence number 13
and 14 too; the unlocked rows are allocated new sequence numbers 1, 2, 3
and the locked rows remain unchanged.  One of the comments to the
question asks about '1 locked, 5 unlocked, 10 locked'; this would
produce '1 locked, 2 unlocked, 10 locked'.

Getting to do that in SQL takes quite a lot of SQL.  Someone with a good
command of the OLAP functionality might be able to get there quicker
than my code does.  And converting the SELECT results into an UPDATE
statement is tricky too (and not fully solved by me).  But being able to
get the data presented in the correct result order is crucial, and the
key to solving that is the ordering steps represented by lists A and B.

<hr>

## TDQD &mdash; Test Driven Query Design

As with any complex SQL query operation, the secret is to build the
query up step by step.  As noted, we need to treat locked and unlocked
rows differently.  In this case, the target is ultimately an UPDATE
statement, but we need to know how to generate the data for the UPDATE,
so we do the SELECT first.

### Renumberable rows

    -- Query 1
    SELECT Name, Seq_No
      FROM My_Table
     WHERE Locked = 'N'
     ORDER BY Seq_No;

    NAME  SEQ_NO
    Foo   1
    Baz   5
    Cde   7

When appropriate, these can be ordered with an ORDER BY clause, but
sub-queries typically don't allow ORDER BY clauses and we need to
generate a number.  With OLAP functions, you can probably do this more
compactly.  In Oracle, you may be able to use ROWNUM to generate row
numbers.  There's a trick that will work in any DBMS, though it is not
particularly fast.

### Renumbered rows assuming no interference from locked rows

    -- Query 2
    SELECT m1.Name, m1.Seq_No AS Old_Seq, COUNT(*) AS New_Seq
      FROM My_Table m1
      JOIN My_Table m2
        ON m1.Seq_No >= m2.Seq_No
     WHERE m1.Locked = 'N' AND m2.Locked = 'N'
     GROUP BY m1.Name, m1.Seq_No
     ORDER BY New_Seq;

    NAME  Old_Seq   New_Seq
    Foo   1         1
    Baz   5         2
    Cde   7         3

This is a non-equijoin and that is what makes this a not particularly fast operation.

### Unrenumberable rows

    -- Query 3
    SELECT Name, Seq_No
      FROM My_Table
     WHERE Locked = 'Y'
     ORDER BY Seq_No;

    NAME  Seq_No
    Bar   3
    Abc   4

### New sequence numbers

Suppose we manage to get a list of numbers, 1..N (where N = 5 in the
sample data).  We remove from that list the locked entries (3, 4)
leaving (1, 2, 5).  When those are ranked (1 = 1, 2 = 2, 3 = 5), we can
join the ranking with the unlocked records new sequence, but use the
other number as the final sequence number of the record.  That just
leaves us with a few little problems to resolve.  First, generating each
of the numbers 1..N; we can do one of those ghastly little non-equijoin
tricks, but there should be a better way:

    -- Query 4
    SELECT COUNT(*) AS Ordinal
      FROM My_Table AS t1
      JOIN My_Table AS t2
        ON t1.Seq_No >= t2.Seq_No
     GROUP BY t1.Seq_No
     ORDER BY Ordinal;

    Ordinal
    1
    2
    3
    4
    5

We can then remove the locked sequence numbers from this list:

    -- Query 5
    SELECT Ordinal
      FROM (SELECT COUNT(*) AS ordinal
              FROM My_Table t1
              JOIN My_Table t2
                ON t1.Seq_No <= t2.Seq_No
             GROUP BY t1.Seq_No
           ) O
     WHERE O.Ordinal NOT IN (SELECT Seq_No FROM My_Table WHERE Locked = 'Y')
     ORDER BY Ordinal;

     Ordinal
     1
     2
     5

Now we need to rank those, which means another of the self-joins, but
this time on that expression.  Time to use 'Common Table Expressions' or
CTE, also known as a 'WITH clause':

    -- Query 6
    WITH HoleyList AS
        (SELECT ordinal
           FROM (SELECT COUNT(*) ordinal
                   FROM My_Table t1
                   JOIN My_Table t2
                     ON t1.seq_no <= t2.seq_no
                  GROUP BY t1.seq_no
                ) O
          WHERE O.Ordinal NOT IN (SELECT Seq_No FROM My_Table WHERE Locked = 'Y')
        )
    SELECT H1.Ordinal, COUNT(*) AS New_Seq
      FROM HoleyList H1
      JOIN HoleyList H2
        ON H1.Ordinal >= H2.Ordinal
     GROUP BY H1.Ordinal
     ORDER BY New_Seq;

    Ordinal  New_Seq
    1        1
    2        2
    5        3

### Finishing up

So, now we need to join that result with Query 2 to get the final
numbers for the unlocked rows, and then the union of that with Query 3
to get the required output.  Of course, we have to get the correct
values for Locked in the output too.  Still going step-wise:

    -- Query 7
    WITH
    Query2 AS
       (SELECT m1.Name, m1.Seq_No AS Old_Seq, COUNT(*) AS New_Seq
          FROM My_Table m1
          JOIN My_Table m2 ON m1.Seq_No <= m2.Seq_No
         WHERE m1.Locked = 'N' AND m2.Locked = 'N'
         GROUP BY m1.Name, m1.Seq_No
       ),
    HoleyList AS
       (SELECT ordinal
          FROM (SELECT COUNT(*) AS ordinal
                  FROM My_Table t1
                  JOIN My_Table t2
                    ON t1.seq_no <= t2.seq_no
                 GROUP BY t1.seq_no
               ) O
          WHERE O.Ordinal NOT IN (SELECT Seq_No FROM My_Table WHERE Locked = 'Y')
        ),
    Reranking AS    
       (SELECT H1.Ordinal, COUNT(*) AS New_Seq
          FROM HoleyList H1
          JOIN HoleyList H2
            ON H1.Ordinal >= H2.Ordinal
         GROUP BY H1.Ordinal
       )
    SELECT r.Ordinal, r.New_Seq, q.Name, q.Old_Seq, 'N' Locked
      FROM Reranking r
      JOIN Query2    q
        ON r.New_Seq = q.New_Seq
     ORDER BY r.New_Seq;

    Ordinal  New_Seq  Name  Old_Seq  Locked
    1        1        Cde   7        N
    2        2        Baz   5        N
    5        3        Foo   1        N

This needs to be combined with a variant of Query 3:

    -- Query 3a
    SELECT Seq_No Ordinal, Seq_No New_Seq, Name, Seq_No Old_Seq, Locked
      FROM My_Table
     WHERE Locked = 'Y'
     ORDER BY New_Seq;

    Ordinal  New_Seq  Name  Old_Seq  Locked
    3        3        Bar   3        Y
    4        4        Abc   4        Y

### The result set

Combining these yields:

    -- Query 8
    WITH
    Query2 AS
       (SELECT m1.Name, m1.Seq_No AS Old_Seq, COUNT(*) AS New_Seq
          FROM My_Table m1
          JOIN My_Table m2 ON m1.Seq_No <= m2.Seq_No
         WHERE m1.Locked = 'N' AND m2.Locked = 'N'
         GROUP BY m1.Name, m1.Seq_No
       ),
    HoleyList AS
       (SELECT ordinal
          FROM (SELECT COUNT(*) AS ordinal
                  FROM My_Table t1
                  JOIN My_Table t2
                    ON t1.seq_no <= t2.seq_no
                 GROUP BY t1.seq_no
               ) O
          WHERE O.Ordinal NOT IN (SELECT Seq_No FROM My_Table WHERE Locked = 'Y')
        ),
    Reranking AS    
       (SELECT H1.Ordinal, COUNT(*) AS New_Seq
          FROM HoleyList H1
          JOIN HoleyList H2
            ON H1.Ordinal >= H2.Ordinal
         GROUP BY H1.Ordinal
       ),
    Query7 AS
       (SELECT r.Ordinal, r.New_Seq, q.Name, q.Old_Seq, 'N' Locked
          FROM Reranking r
          JOIN Query2    q
            ON r.New_Seq = q.New_Seq
       ),
    Query3a AS
       (SELECT Seq_No Ordinal, Seq_No New_Seq, Name, Seq_No Old_Seq, Locked
          FROM My_Table
         WHERE Locked = 'Y'
       )
    SELECT Ordinal, New_Seq, Name, Old_Seq, Locked
      FROM Query7
    UNION
    SELECT Ordinal, New_Seq, Name, Old_Seq, Locked
      FROM Query3a
     ORDER BY New_Seq;

This gives the result:

    Ordinal  New_Seq  Name  Old_Seq  Locked
    1        1        Cde   7        N
    2        2        Baz   5        N
    3        3        Bar   3        Y
    4        4        Abc   4        Y
    5        3        Foo   1        N

So, it is possible (though far from easy) to write a SELECT statement that orders the data correctly.

### Converting into an UPDATE operation

Now we have to find a way to get that monstrosity into an UPDATE
statement.  Left to my own devices, I'd think in terms of a transaction
that selects the result of Query 8 into a temporary table, then deletes
all the records from the source table (`My_Table`) and inserts the
appropriate project of the result of Query 8 into the original table and
then commits.

Oracle doesn't seem to support dynamically created 'per session'
temporary tables; only global temporary tables.  And there are sound
reasons not to use those, for all they are SQL Standard.  Nevertheless,
it will do the trick here where I'm not sure what else will work:

Separately from this work:

    CREATE GLOBAL TEMPORARY TABLE ReSequenceTable
    (
        Name     CHAR(3) NOT NULL,
        Seq_No   INTEGER NOT NULL,
        Locked   CHAR(1) NOT NULL
    )
    ON COMMIT DELETE ROWS;

Then:


    -- Query 8a
    BEGIN;   -- May be unnecessary and/or unsupported in Oracle
    INSERT INTO ReSequenceTable(Name, Seq_No, Locked)
        WITH
        Query2 AS
           (SELECT m1.Name, m1.Seq_No AS Old_Seq, COUNT(*) AS New_Seq
              FROM My_Table m1
              JOIN My_Table m2 ON m1.Seq_No <= m2.Seq_No
             WHERE m1.Locked = 'N' AND m2.Locked = 'N'
             GROUP BY m1.Name, m1.Seq_No
           ),
        HoleyList AS
           (SELECT ordinal
              FROM (SELECT COUNT(*) AS ordinal
                      FROM My_Table t1
                      JOIN My_Table t2
                        ON t1.seq_no <= t2.seq_no
                     GROUP BY t1.seq_no
                   ) O
              WHERE O.Ordinal NOT IN (SELECT Seq_No FROM My_Table WHERE Locked = 'Y')
            ),
        Reranking AS    
           (SELECT H1.Ordinal, COUNT(*) AS New_Seq
              FROM HoleyList H1
              JOIN HoleyList H2
                ON H1.Ordinal >= H2.Ordinal
             GROUP BY H1.Ordinal
           ),
        Query7 AS
           (SELECT r.Ordinal, r.New_Seq, q.Name, q.Old_Seq, 'N' Locked
              FROM Reranking r
              JOIN Query2    q
                ON r.New_Seq = q.New_Seq
           ),
        Query3a AS
           (SELECT Seq_No Ordinal, Seq_No New_Seq, Name, Seq_No Old_Seq, Locked
              FROM My_Table
             WHERE Locked = 'Y'
           )
        SELECT Name, Ordinal, Locked
          FROM Query7
        UNION
        SELECT Name, Ordinal, Locked
          FROM Query3a;

    DELETE FROM My_Table;
    INSERT INTO My_Table(Name, Seq_No, Locked) FROM ReSequenceTable;
    COMMIT;

You probably can do it with an appropriate UPDATE; you need to do some of the thinking.

<hr>

## Summary

It isn't easy, but it can be done.

The _key step_ (at least for me) was the result set from _Query 6_,
which worked out the new positions of the unlocked rows in the updated
result set.  That is not immediately obvious, but it is crucial to
producing the answer.

The rest is simply support code wrapped around that key step.

As noted previously, there are likely to be many ways to improve some of
the queries.  For example, generating the sequence `1..N` from the table
might be as simple as `SELECT ROWNUM FROM My_Table`, which compacts the
query (highly beneficial &mdash; it is verbose).  There are OLAP
functions; one or more of those may be able to help with the ranking
operations (probably more concisely; like performing better too).

So, this is not a polished final answer; but it is a strong push in the
right general direction.

<hr>

### PoC Testing

The code has been tested against Informix.  I had to use somewhat
different notations because Informix does not (yet) support CTEs.  It
does have very convenient, very simple, per session dynamic temporary
tables introduced by `INTO TEMP <temp-table-name>` which appears where
the ORDER BY clause might otherwise appear.  Thus, I simulated Query 8a
with:

    + BEGIN;
    + SELECT O.Ordinal
      FROM (SELECT COUNT(*) AS ordinal
              FROM My_Table AS t1
              JOIN My_Table AS t2
                ON t1.Seq_No <= t2.Seq_No
             GROUP BY t1.Seq_No
           ) AS O
     WHERE O.Ordinal NOT IN (SELECT Seq_No FROM My_Table WHERE Locked = 'Y')
     INTO TEMP HoleyList;
    + SELECT * FROM HoleyList ORDER BY Ordinal;
    1
    2
    5
    + SELECT H1.Ordinal, COUNT(*) AS New_Seq
      FROM HoleyList AS H1
      JOIN HoleyList AS H2
        ON H1.Ordinal >= H2.Ordinal
     GROUP BY H1.Ordinal
     INTO TEMP ReRanking;
    + SELECT * FROM ReRanking ORDER BY Ordinal;
    1|1
    2|2
    5|3
    + SELECT m1.Name, m1.Seq_No AS Old_Seq, COUNT(*) AS New_Seq
      FROM My_Table m1
      JOIN My_Table m2
        ON m1.Seq_No >= m2.Seq_No
     WHERE m1.Locked = 'N' AND m2.Locked = 'N'
     GROUP BY m1.Name, m1.Seq_No
      INTO TEMP Query2;
    + SELECT * FROM Query2 ORDER BY New_Seq;
    Foo|1|1
    Baz|5|2
    Cde|7|3
    + SELECT r.Ordinal, r.New_Seq, q.Name, q.Old_Seq, 'N' Locked
      FROM Reranking r
      JOIN Query2    q
        ON r.New_Seq = q.New_Seq
      INTO TEMP Query7;
    + SELECT * FROM Query7 ORDER BY Ordinal;
    1|1|Foo|1|N
    2|2|Baz|5|N
    5|3|Cde|7|N
    + SELECT Seq_NO Ordinal, Seq_No New_Seq, Name, Seq_No Old_Seq, Locked
      FROM My_Table
     WHERE Locked = 'Y'
      INTO TEMP Query3a;
    + SELECT * FROM Query3a ORDER BY Ordinal;
    3|3|Bar|3|Y
    4|4|Abc|4|Y
    + SELECT Ordinal, New_Seq, Name, Old_Seq, Locked
      FROM Query7
    UNION
    SELECT Ordinal, New_Seq, Name, Old_Seq, Locked
      FROM Query3a
      INTO TEMP Query8;
    + SELECT * FROM Query8 ORDER BY Ordinal;
    1|1|Foo|1|N
    2|2|Baz|5|N
    3|3|Bar|3|Y
    4|4|Abc|4|Y
    5|3|Cde|7|N
    + ROLLBACK;

