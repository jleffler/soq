https://stackoverflow.com/questions/13132270/how-to-select-similar-sets-in-sql

You specify

> How can I write a query that can select all orders that are at least
> 85% similar to a specific order?

This is an important simplification compared with 'all pairs of orders
that are at least 85% similar to each other'.

We'll use some TDQD (Test-Driven Query Design) and some analysis to help us.

### Preliminaries

To be remotely similar, the two orders must have at least one item in
common.  This query can be used to determine which orders have at least
one item in common with a specified order:

    SELECT DISTINCT I1.ID
      FROM OrderItem AS I1
      JOIN OrderItem AS I2 ON I2.ItemID = I1.ItemID AND I2.OrderID = <specified order ID>
     WHERE I1.OrderID != <specified order ID>

This prunes the list of other orders to be examined quite a lot, though
if the specified order included one of your most popular items, it's
likely that a lot of other orders also did so.

Instead of the DISTINCT, you could use:

    SELECT I1.ID, COUNT(*) AS Num_Common
      FROM OrderItem AS I1
      JOIN OrderItem AS I2 ON I2.ItemID = I1.ItemID AND I2.OrderID = <specified order ID>
     WHERE I1.OrderID != <specified order ID>
     GROUP BY I1.ID

This gives you the number of items in an order that it has in common
with the specified order.  We also need the number of items in each
order:

    SELECT ID, COUNT(*) AS Num_Total
      FROM OrderItem
     GROUP BY OrderID;

### Identical Orders

For 100% similarity, the two orders would have as many items in common
as each has items.  This would probably not find many pairs of orders,
though.  We can find the orders with exactly the same items as the
specified order easily enough:

    SELECT L1.ID
      FROM (SELECT ID, COUNT(*) AS Num_Total
              FROM OrderItem
             GROUP BY OrderID;
           ) AS L1
      JOIN (SELECT I1.ID, COUNT(*) AS Num_Common
              FROM OrderItem AS I1
              JOIN OrderItem AS I2 ON I2.ItemID = I1.ItemID AND I2.OrderID = <specified order ID>
             WHERE I1.OrderID != <specified order ID>
             GROUP BY I1.ID
           ) AS L2 ON L1.ID = L2.ID AND L1.Num_Total = L2.Num_Common;

### Similar Orders — Analyzing the Formula

Applying the [Jaccard Similarity](http://en.wikipedia.org/wiki/Jaccard_index)
as defined at Wikipedia to two orders A and B, with |A| being the count
of the number of items in order A, the Jaccard Similarity _J(A,B) =
|A∩B| ÷ |A∪B|_, where |A∩B| is the number of items in common to
the two orders and |A∪B| is the total number of different items
ordered.

To meet an 85% Jaccard Similarity criterion, if the number of items in
either order is less than some threshold, the orders must be identical.
For example, if both orders A and B have 5 items, say, but there's one
item different between the two, it gives you 4 items in common (|A∩B|)
and 6 items in total (|A∪B|), so the Jaccard Similarity J(A,B) is only
66⅔%.

For 85% similarity when there are N items in each of the two orders and
1 item is different, _(N-1) ÷ (N+1) ≥ 0.85_, which means N > 12
(12⅓ to be precise).  For a fraction F = J(A,B), one item different
means _(N-1) ÷ (N+1) ≥ F_ which can be solved for N giving _N ≥ (1
+ F) ÷ (1 - F)_.  As the similarity requirement goes up, the orders
must be identical for increasingly large values of N.

Generalizing still further, let's suppose we have different size orders
with N and M items (without loss of generality, N < M).  The maximum
value of |A∩B| is now N and the minimum value of |A∪B| is M (meaning
all the items in the smaller order appear in the larger order).  Let's
define that M = N + ∆, and that there are ∂ items present in the
smaller order that are not present in the larger order.  It follows that
there are ∆+∂ items present in the larger order that are not in the
smaller order.

By definition, then, |A∩B| = N-∂, and |A∪B| = (N-∂) + ∂ +
(N+∆-(N-∂)), where the three added terms represent (1) the number of
items in common between the two orders, (2) the number of items only in
the smaller order, and (3) the number of items only in the larger order.
This simplifies to: |A∪B| = N+∆+∂.

<hr>

### Key Equation

For a similarity fraction F, we're interested in pairs of orders where
J(A,B) ≥ F, so:

> (N-∂) ÷ (N+∆+∂) ≥ F

> F ≤ (N-∂) ÷ (N+∆+∂)

<hr>

We can use a spreadsheet to graph the relationship between these.  For a
given number of items in the smaller order (x-axis), and for a given
similarity, we can graph the maximum value of ∂ that gives us a
similarity of F.  The formula is:

> ∂ = (N(1-F) - F∆) ÷ (1+F)

...image...

This is a linear equation in N and ∆ for constant F; it is non-linear
for different values of F.  Clearly, ∂ has to be a non-negative
integer.

Given F = 0.85, for orders that are the same size (∆=0), for 1 ≤ N <
13, ∂ = 0; for 13 ≤ N < 25, ∂ ≤ 1; for 25 ≤ N < 37, ∂ ≤ 2,
for 37 ≤ N < 50, ∂ ≤ 3.

For orders that differ by 1 (∆=1), for 1 ≤ N < 18, ∂ = 0; for 18
≤ N < 31, ∂ ≤ 1; for 31 ≤ N < 43, ∂ ≤ 2; etc.  If ∆=6, you
need N=47 before the orders are still 85% similar with ∂=1.  That
means the small order has 47 items, of which 46 are in common with the
large order of 53 items.

### Similar Orders — Applying the Analysis

So far, so good.  How can we apply that theory to selecting the orders
similar to a specified order?

First, we observe that the specified order could be the same size as a
similar order, or larger, or smaller.  This complicates things a bit.

The parameters of the equation above are:

* N – number of items in smaller order
* ∆ — difference between number of items in larger order and N
* F — fixed
* ∂ — number of items in smaller order not matched in larger order

The values available using minor variations on the queries developed at the top:

* NC — number of items in common
* NA — number of items in specified order
* NB — number of items in compared order

    SELECT ID, COUNT(*) AS NA
      FROM OrderItem
     WHERE OrderID = <specified order ID>
     GROUP BY OrderID;

    SELECT ID, COUNT(*) AS NB
      FROM OrderItem
     WHERE OrderID != <specified order ID>
     GROUP BY OrderID;

    SELECT I1.ID, COUNT(*) AS NC
      FROM OrderItem AS I1
      JOIN OrderItem AS I2 ON I2.ItemID = I1.ItemID AND I2.OrderID = <specified order ID>
     WHERE I1.OrderID != <specified order ID>
     GROUP BY I1.ID

For convenience, we want the values N and N+∆ (and hence ∆) available, so
we can use a UNION to arrange things appropriately, with:

* NS = N — number of items in smaller order
* NL = N + ∆ — number of items in larger order

and in the second version of the UNION query, with:

* NC = N - ∂ — number of items in common

Both queries keep the two order ID numbers so that you can track back to
the rest of the order information later.

    SELECT v1.ID AS OrderID_1, v1.NA AS NS, v2.ID AS OrderID_2, v2.NB AS NL
      FROM (SELECT ID, COUNT(*) AS NA
              FROM OrderItem
             WHERE OrderID = <specified order ID>
             GROUP BY OrderID
           ) AS v1
      JOIN (SELECT ID, COUNT(*) AS NB
              FROM OrderItem
             WHERE OrderID != <specified order ID>
             GROUP BY OrderID
           ) AS v2
        ON v1.NA <= v2.NB
    UNION
    SELECT v2.ID AS OrderID_1, v2.NB AS NS, v1.ID AS OrderID_2, v2.NA AS NL
      FROM (SELECT ID, COUNT(*) AS NA
              FROM OrderItem
             WHERE OrderID = <specified order ID>
             GROUP BY OrderID
           ) AS v1
      JOIN (SELECT ID, COUNT(*) AS NB
              FROM OrderItem
             WHERE OrderID != <specified order ID>
             GROUP BY OrderID
           ) AS v2
        ON v1.NA > v2.NB

This gives us a table expression with columns OrderID_1, NS, OrderID_2,
NL, where NS is the number of items in the 'smaller order and NL is the
number of items in the larger order.  Since there is no overlap in the
order numbers generated by the v1 and v2 table expressions, there's no
need to worry about 'reflexive' entries where the OrderID values are the
same.  Adding NC to this is most easily handled in the UNION query too:

    SELECT v1.ID AS OrderID_1, v1.NA AS NS, v2.ID AS OrderID_2, v2.NB AS NL, v3.NC AS NC
      FROM (SELECT ID, COUNT(*) AS NA
              FROM OrderItem
             WHERE OrderID = <specified order ID>
             GROUP BY OrderID
           ) AS v1
      JOIN (SELECT ID, COUNT(*) AS NB
              FROM OrderItem
             WHERE OrderID != <specified order ID>
             GROUP BY OrderID
           ) AS v2
        ON v1.NA <= v2.NB
      JOIN (SELECT I1.ID, COUNT(*) AS NC
              FROM OrderItem AS I1
              JOIN OrderItem AS I2 ON I2.ItemID = I1.ItemID AND I2.OrderID = <specified order ID>
             WHERE I1.OrderID != <specified order ID>
             GROUP BY I1.ID
           ) AS v3
        ON v3.ID = v2.ID
    UNION
    SELECT v2.ID AS OrderID_1, v2.NB AS NS, v1.ID AS OrderID_2, v2.NA AS NL, v3.NC AS NC
      FROM (SELECT ID, COUNT(*) AS NA
              FROM OrderItem
             WHERE OrderID = <specified order ID>
             GROUP BY OrderID
           ) AS v1
      JOIN (SELECT ID, COUNT(*) AS NB
              FROM OrderItem
             WHERE OrderID != <specified order ID>
             GROUP BY OrderID
           ) AS v2
        ON v1.NA > v2.NB
      JOIN (SELECT I1.ID, COUNT(*) AS NC
              FROM OrderItem AS I1
              JOIN OrderItem AS I2 ON I2.ItemID = I1.ItemID AND I2.OrderID = <specified order ID>
             WHERE I1.OrderID != <specified order ID>
             GROUP BY I1.ID
           ) AS v3
        ON v3.ID = v1.ID

This gives us a table expression with columns OrderID_1, NS, OrderID_2,
NL, NC, where NS is the number of items in the 'smaller order and NL is
the number of items in the larger order, and NC is the number of items
in common.

Given NS, NL, NC, we are looking for orders that satisfy:

> (N-∂) ÷ (N+∆+∂) ≥ F.

* N – number of items in smaller order
* ∆ — difference between number of items in larger order and N
* F — fixed
* ∂ — number of items in smaller order not matched in larger order

* NS = N — number of items in smaller order
* NL = N + ∆ — number of items in larger order
* NC = N - ∂ — number of items in common

The condition, therefore, needs to be:

    NC / (NL + (NS - NC)) ≥ F

The term on the LHS must be evaluated as a floating point number, not as
an integer expression.  Applying that to the UNION query above, yields:

    SELECT OrderID_1, NS, OrderID_2, NL, NC,
            CAST(NC AS NUMERIC) / CAST(NL + NS - NC AS NUMERIC) AS Similarity
      FROM (SELECT v1.ID AS OrderID_1, v1.NA AS NS, v2.ID AS OrderID_2, v2.NB AS NL, v3.NC AS NC
              FROM (SELECT ID, COUNT(*) AS NA
                      FROM OrderItem
                     WHERE OrderID = <specified order ID>
                     GROUP BY OrderID
                   ) AS v1
              JOIN (SELECT ID, COUNT(*) AS NB
                      FROM OrderItem
                     WHERE OrderID != <specified order ID>
                     GROUP BY OrderID
                   ) AS v2
                ON v1.NA <= v2.NB
              JOIN (SELECT I1.ID, COUNT(*) AS NC
                      FROM OrderItem AS I1
                      JOIN OrderItem AS I2 ON I2.ItemID = I1.ItemID AND I2.OrderID = <specified order ID>
                     WHERE I1.OrderID != <specified order ID>
                     GROUP BY I1.ID
                   ) AS v3
                ON v3.ID = v2.ID
            UNION
            SELECT v2.ID AS OrderID_1, v2.NB AS NS, v1.ID AS OrderID_2, v2.NA AS NL, v3.NC AS NC
              FROM (SELECT ID, COUNT(*) AS NA
                      FROM OrderItem
                     WHERE OrderID = <specified order ID>
                     GROUP BY OrderID
                   ) AS v1
              JOIN (SELECT ID, COUNT(*) AS NB
                      FROM OrderItem
                     WHERE OrderID != <specified order ID>
                     GROUP BY OrderID
                   ) AS v2
                ON v1.NA > v2.NB
              JOIN (SELECT I1.ID, COUNT(*) AS NC
                      FROM OrderItem AS I1
                      JOIN OrderItem AS I2 ON I2.ItemID = I1.ItemID AND I2.OrderID = <specified order ID>
                     WHERE I1.OrderID != <specified order ID>
                     GROUP BY I1.ID
                   ) AS v3
                ON v3.ID = v1.ID
           ) AS u
     WHERE CAST(NC AS NUMERIC) / CAST(NL + NS - NC AS NUMERIC) >= 0.85 -- F

You might observe that this query only uses the OrderItem table; the
Order and Item tables are not needed.

<hr>

Warning: untested SQL (caveat lector).

There may be more compact ways of expressing the query, possibly using
the OLAP functions.

If I was going to test this, I'd create a table with a few
representative sets of order items, checking that the similarity measure
returned was sensible.  I'd work the queries more or less as shown,
gradually building up the complex query.  If one of the expressions was
shown to be flawed, then I'd make appropriate adjustments in that query
until the flaw was fixed.

Clearly, performance will be an issue.  The innermost queries are not
dreadfully complex, but they aren't wholy trivial.  However, measurement
will show whether it's a dramatic problem or just a nuisance.  Studying
the query plans may help.  It seems very probable that there should be
an index on OrderItem.OrderID; the queries are unlikely to perform well
if there isn't such an index.  That is unlikely to be a problem since it
is a foreign key column.


### Using Common Table Expressions

Using common table expressions clarifies to the optimizer when
expressions are the same, and may help it perform better.  They also
help the humans reading your query.  The query above does rather beg for
the use of CTEs.

Version 1: Repeating the specified order number

    WITH SO AS (SELECT ID, COUNT(*) AS NA       -- Specified Order (SO)
                  FROM OrderItem
                 WHERE OrderID = <specified order ID>
                 GROUP BY OrderID
               ),
         OO AS (SELECT ID, COUNT(*) AS NB       -- Other orders (OO)
                  FROM OrderItem
                 WHERE OrderID != <specified order ID>
                 GROUP BY OrderID
               ),
         CI AS (SELECT I1.ID, COUNT(*) AS NC    -- Common Items (CI)
                  FROM OrderItem AS I1
                  JOIN OrderItem AS I2 ON I2.ItemID = I1.ItemID AND I2.OrderID = <specified order ID>
                 WHERE I1.OrderID != <specified order ID>
                 GROUP BY I1.ID
               )
    SELECT OrderID_1, NS, OrderID_2, NL, NC,
            CAST(NC AS NUMERIC) / CAST(NL + NS - NC AS NUMERIC) AS Similarity
      FROM (SELECT v1.ID AS OrderID_1, v1.NA AS NS, v2.ID AS OrderID_2, v2.NB AS NL, v3.NC AS NC
              FROM SO AS v1
              JOIN OO AS v2 ON v1.NA <= v2.NB
              JOIN CI AS v3 ON v3.ID  = v2.ID
            UNION
            SELECT v2.ID AS OrderID_1, v2.NB AS NS, v1.ID AS OrderID_2, v2.NA AS NL, v3.NC AS NC
              FROM SO AS v1
              JOIN OO AS v2 ON v1.NA  > v2.NB
              JOIN CI AS v3 ON v3.ID  = v1.ID
           ) AS u
     WHERE CAST(NC AS NUMERIC) / CAST(NL + NS - NC AS NUMERIC) >= 0.85 -- F

Version 2: Avoiding repeating the specified order number

    WITH SO AS (SELECT ID, COUNT(*) AS NA       -- Specified Order (SO)
                  FROM OrderItem
                 WHERE OrderID = <specified order ID>
                 GROUP BY OrderID
               ),
         OO AS (SELECT OI.ID, COUNT(*) AS NB    -- Other orders (OO)
                  FROM OrderItem AS OI
                  JOIN SO ON OI.OrderID != SO.ID
                 GROUP BY OrderID
               ),
         CI AS (SELECT I1.ID, COUNT(*) AS NC    -- Common Items (CI)
                  FROM OrderItem AS I1
                  JOIN SO AS S1 ON I1.OrderID != S1.ID
                  JOIN OrderItem AS I2 ON I2.ItemID = I1.ItemID
                  JOIN SO AS S2 ON I2.OrderID  = S2.ID
                 GROUP BY I1.ID
               )
    SELECT OrderID_1, NS, OrderID_2, NL, NC,
            CAST(NC AS NUMERIC) / CAST(NL + NS - NC AS NUMERIC) AS Similarity
      FROM (SELECT v1.ID AS OrderID_1, v1.NA AS NS, v2.ID AS OrderID_2, v2.NB AS NL, v3.NC AS NC
              FROM SO AS v1
              JOIN OO AS v2 ON v1.NA <= v2.NB
              JOIN CI AS v3 ON v3.ID  = v2.ID
            UNION
            SELECT v2.ID AS OrderID_1, v2.NB AS NS, v1.ID AS OrderID_2, v2.NA AS NL, v3.NC AS NC
              FROM SO AS v1
              JOIN OO AS v2 ON v1.NA  > v2.NB
              JOIN CI AS v3 ON v3.ID  = v1.ID
           ) AS u
     WHERE CAST(NC AS NUMERIC) / CAST(NL + NS - NC AS NUMERIC) >= 0.85 -- F

