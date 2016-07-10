-- SO 33104874
-- Various queries to solve question

-- Quote: 'this works'
-- SELECT * FROM mytable, TABLE(myfunc('some literal')) vt(result);
-- Quote: 'this gets -999 not implemented yet'
-- SELECT * FROM mytable, TABLE(myfunc(value)) vt(result);

-- Adapting 'this works' to Stores database with US_States and Elements tables
-- It does work
-- SELECT *
--   FROM Elements, TABLE(states_starting('M')) vt(result)
-- ;
--
-- The vt(result) gives a name to the table and the column returned
-- SELECT *
--   FROM Elements, TABLE(states_starting('M')) AS vt(result)
-- ;

-- This works, as claimed
SELECT *
  FROM Elements JOIN TABLE(states_starting('M')) AS vt(result)
    ON Elements.Symbol[1] = vt.result[1]
 ORDER BY Elements.Atomic_Number
;

-- This fails with column name (or SLV) unknown.
-- That's not identical to the -999 claimed.
-- The failure makes some sort of sense; in the TABLE(...) expression,
-- the alias e (probably) isn't known.
-- To generate the complete "correct" result, the TABLE(...) expression
-- would have to be evaluated multiple times, once for each separate
-- initial letter.  So, you'd need a set of table results.
SELECT *
  FROM Elements AS e
  JOIN TABLE(states_starting(e.name[1])) AS vt(result)
    ON Elements.Symbol[1] = vt.result[1]
 ORDER BY Elements.Atomic_Number
;

-- We'd need some sort of correlated sub-query here; how might it be done?
SELECT *
  FROM Elements AS e
  JOIN TABLE(states_starting(name)) AS vt(result)
    ON Elements.Symbol[1] = vt.result[1]
 ORDER BY Elements.Atomic_Number
;
