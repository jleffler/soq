-- TDQD Step 1
-- Employees who have sold the book 'Quickbooks for Business'

SELECT e.eno
  FROM employee AS e
  JOIN salesorder AS o ON o.eno = e.eno
  JOIN orderline AS l ON o.ono = l.ono
  JOIN book AS b ON l.bno = b.bno
 WHERE b.bname = 'Quickbooks for Business';

-- TDQD Step 2
-- Customers who have placed an order from a list of employees

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

-- TDQD Step 3
-- Cities of customers who have place an order from a list of employees

SELECT DISTINCT z.city
  FROM customer AS c
  JOIN salesorder AS o ON c.cno = o.cno
  JOIN zipcode AS z ON z.zip = c.zip
 WHERE o.eno IN
       (SELECT e.eno
          FROM employee AS e
          JOIN salesorder AS o ON o.eno = e.eno
          JOIN orderline AS l ON o.ono = l.ono
          JOIN book AS b ON l.bno = b.bno
         WHERE b.bname = 'Quickbooks for Business'
       )
 ORDER BY z.city;

-- TDQD Step 4
-- Do not use a sub-query

SELECT DISTINCT z.city
  FROM customer AS c
  JOIN salesorder AS o1 ON c.cno = o1.cno
  JOIN zipcode AS z ON z.zip = c.zip
  JOIN employee AS e ON o1.eno = e.eno
  JOIN salesorder AS o2 ON o2.eno = e.eno
  JOIN orderline AS l ON o2.ono = l.ono
  JOIN book AS b ON l.bno = b.bno
 WHERE b.bname = 'Quickbooks for Business'
 ORDER BY z.city;

{
Get names of cities of customers who have placed an order through
employees who have sold the book "Quickbooks for Business".

Required: you must complete this query with sub select.
}