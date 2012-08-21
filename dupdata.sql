BEGIN;

CREATE TABLE T1
(ID INTEGER NOT NULL PRIMARY KEY, a CHAR(1) NOT NULL, b CHAR(1) NOT  NULL);

INSERT INTO T1 VALUES(1, 'k', 'l');
INSERT INTO T1 VALUES(2, 'k', 'l');
INSERT INTO T1 VALUES(3, 'a', 'b');
INSERT INTO T1 VALUES(4, 'p', 'q');
INSERT INTO T1 VALUES(5, 't', 'v');

CREATE TABLE T2
(IDFK INTEGER NOT NULL REFERENCES T1, c CHAR(1) NOT NULL, d CHAR(1) NOT  NULL);

INSERT INTO T2 VALUES(1, 'w', 'x');
INSERT INTO T2 VALUES(1, 'y', 'z');
INSERT INTO T2 VALUES(2, 'w', 'x');
INSERT INTO T2 VALUES(2, 'w', 'x');
INSERT INTO T2 VALUES(2, 'y', 'z');
INSERT INTO T2 VALUES(3, 'w', 'x');
INSERT INTO T2 VALUES(3, 'y', 'b');
INSERT INTO T2 VALUES(3, 'y', 'z');
INSERT INTO T2 VALUES(4, 'w', 'x');
INSERT INTO T2 VALUES(5, 'w', 'x');
INSERT INTO T2 VALUES(5, 'y', 'z');
INSERT INTO T2 VALUES(5, 'w', 'x');
INSERT INTO T2 VALUES(5, 'y', 'z');

SELECT DISTINCT idfk AS id, c, d FROM t2 WHERE idfk != 1;
SELECT DISTINCT idfk AS id, c, d FROM t2 WHERE idfk  = 1;

SELECT id, COUNT(*) FROM (SELECT DISTINCT idfk AS id, c, d FROM t2 WHERE idfk != 1) AS x GROUP BY id;
SELECT id, COUNT(*) FROM (SELECT DISTINCT idfk AS id, c, d FROM t2 WHERE idfk  = 1) AS x GROUP BY id;

-- Query 5 - IDs having same count of rows as ID = 1
--
--SELECT idfk AS id
--  FROM t2
-- WHERE idfk != 1
-- GROUP BY idfk
--HAVING COUNT(*) = (SELECT COUNT(*) FROM t2 WHERE t2.idfk = 1);

SELECT id
  FROM (SELECT DISTINCT idfk AS id, c, d FROM t2 WHERE idfk != 1) AS x
 GROUP BY id
HAVING COUNT(*) = (SELECT COUNT(*)
                     FROM (SELECT DISTINCT idfk AS id, c, d FROM t2 WHERE idfk  = 1) AS x
                    GROUP BY id);

SELECT idfk AS id, c, d
  FROM t2
  JOIN (SELECT idfk AS id
          FROM t2
         WHERE idfk != 1
         GROUP BY idfk
        HAVING COUNT(*) = (SELECT COUNT(*) FROM t2 WHERE t2.idfk = 1)
       ) AS j2
    ON j2.id = t2.idfk
 ORDER BY id;

SELECT x.id, y.id, x.c, y.c, x.d, y.d
  FROM (SELECT idfk AS id, c, d
          FROM t2
          JOIN (SELECT idfk AS id
                  FROM t2
                 WHERE idfk != 1
                 GROUP BY idfk
                HAVING COUNT(*) = (SELECT COUNT(*) FROM t2 WHERE t2.idfk = 1)
               ) AS j2
            ON j2.id = t2.idfk
       ) AS x
  JOIN (SELECT idfk AS id, c, d
          FROM t2 WHERE idfk = 1
       ) AS y
    ON x.c = y.c AND x.d = y.d
 ORDER BY x.id, y.id, x.c, x.d;

SELECT x.id
  FROM (SELECT idfk AS id, c, d
          FROM t2
          JOIN (SELECT idfk AS id
                  FROM t2
                 WHERE idfk != 1
                 GROUP BY idfk
                HAVING COUNT(*) = (SELECT COUNT(*) FROM t2 WHERE t2.idfk = 1)
               ) AS j2
            ON j2.id = t2.idfk
       ) AS x
  JOIN (SELECT idfk AS id, c, d
          FROM t2 WHERE idfk = 1
       ) AS y
    ON x.c = y.c AND x.d = y.d
 GROUP BY x.id
HAVING COUNT(*) = (SELECT COUNT(*) FROM t2 WHERE t2.idfk = 1);

ROLLBACK;
