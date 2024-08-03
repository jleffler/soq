-- Only using sub-queries
-- TDQD Step 1
-- Book number of 'Quickbooks for Business' (QfB)

SELECT b.bno
  FROM book AS b
 WHERE b.bname = 'Quickbooks for Business';

-- TDQD Step 2
-- Order numbers for orders including QfB

SELECT l.ono
  FROM orderline AS l
 WHERE l.bno IN
       (SELECT b.bno
          FROM book AS b
         WHERE b.bname = 'Quickbooks for Business'
       );

-- TDQD Step 3
-- Employee numbers for orders including QfB

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

-- TDQD Step 4
-- Customer numbers who placed an orders through employees in list

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

-- TDQD Step 5
-- Zip codes of customers who placed orders through employees in list

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

-- TDQD Step 6
-- Cities of customers who placed orders through employees in list

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

