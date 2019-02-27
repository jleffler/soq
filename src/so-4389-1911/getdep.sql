-- Using stored procedure returning row type in SQL
-- Simpler, and more complex, ways of doing it.

DROP PROCEDURE IF EXISTS get_my_dep;

CREATE PROCEDURE get_my_dep(my_dep_num INTEGER)
    RETURNING ROW(dep_code INTEGER, dep_year INTEGER, dep_name VARCHAR(20));
    RETURN ROW(66, 2017, "HR");
END PROCEDURE;

-- SQLCMD doesn't like this!
--EXECUTE PROCEDURE get_my_dep(567);

DROP TABLE IF EXISTS rmcandidate;
CREATE TABLE rmcandidate
(
    task_code INTEGER NOT NULL,
    emp_num   INTEGER NOT NULL
);
INSERT INTO rmcandidate VALUES(12, 567);

DROP TABLE IF EXISTS task;
CREATE TABLE task
(
    task_code INTEGER NOT NULL,
    active_flag SMALLINT NOT NULL
);
INSERT INTO task VALUES(12, 1);

SELECT * 
  FROM rmcandidate a
  JOIN task b
    ON a.task_code = b.task_code
 WHERE b.active_flag = 1;

-- Simpler
SELECT emp_num
  FROM rmcandidate
 WHERE get_my_dep(567).dep_code != 0;

-- Simpler
SELECT * 
  FROM rmcandidate a
  JOIN task b
    ON a.task_code = b.task_code
 WHERE get_my_dep(a.emp_num).dep_code != 0
   AND b.active_flag = 1;

-- More complex (unnecessarily complex in this context)
SELECT * 
  FROM rmcandidate a
  JOIN task b
    ON a.task_code = b.task_code
 WHERE EXISTS(SELECT rt.dep_code FROM TABLE(get_my_dep(a.emp_num)) AS v(rt) WHERE rt.dep_code != 0)
   AND b.active_flag = 1;

