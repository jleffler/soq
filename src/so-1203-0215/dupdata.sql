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

-- Query 5B - IDs having same count of distinct rows as ID = 1
SELECT id
  FROM (SELECT DISTINCT idfk AS id, c, d FROM t2 WHERE idfk != 1) AS x
 GROUP BY id
HAVING COUNT(*) = (SELECT COUNT(*)
                     FROM (SELECT DISTINCT idfk AS id, c, d FROM t2 WHERE idfk  = 1) AS x
                    GROUP BY id);

-- Query 6B
SELECT d2.id, d2.c, d2.d
  FROM (SELECT DISTINCT idfk AS id, c, d FROM t2 WHERE idfk != 1) AS d2
  JOIN (SELECT id
          FROM (SELECT DISTINCT idfk AS id, c, d FROM t2 WHERE idfk != 1) AS x
         GROUP BY id
        HAVING COUNT(*) = (SELECT COUNT(*)
                             FROM (SELECT DISTINCT idfk AS id, c, d FROM t2 WHERE idfk  = 1) AS x
                            GROUP BY id)
       ) AS j2
    ON j2.id = d2.id
 ORDER BY id;

-- Query 7B
SELECT x.id, y.id, x.c, y.c, x.d, y.d
  FROM (SELECT d2.id, d2.c, d2.d
          FROM (SELECT DISTINCT idfk AS id, c, d FROM t2 WHERE idfk != 1) AS d2
          JOIN (SELECT id
                  FROM (SELECT DISTINCT idfk AS id, c, d FROM t2 WHERE idfk != 1) AS x
                 GROUP BY id
                HAVING COUNT(*) = (SELECT COUNT(*)
                                     FROM (SELECT DISTINCT idfk AS id, c, d FROM t2 WHERE idfk  = 1) AS x
                                    GROUP BY id)
               ) AS j2
            ON j2.id = d2.id
       ) AS x
  JOIN (SELECT DISTINCT idfk AS id, c, d FROM t2 WHERE idfk  = 1) AS y
    ON x.c = y.c AND x.d = y.d
 ORDER BY x.id, y.id, x.c, x.d;

-- Query 8B
SELECT x.id
  FROM (SELECT d2.id, d2.c, d2.d
          FROM (SELECT DISTINCT idfk AS id, c, d FROM t2 WHERE idfk != 1) AS d2
          JOIN (SELECT id
                  FROM (SELECT DISTINCT idfk AS id, c, d FROM t2 WHERE idfk != 1) AS x
                 GROUP BY id
                HAVING COUNT(*) = (SELECT COUNT(*)
                                     FROM (SELECT DISTINCT idfk AS id, c, d FROM t2 WHERE idfk  = 1) AS x
                                    GROUP BY id)
               ) AS j2
            ON j2.id = d2.id
       ) AS x
  JOIN (SELECT DISTINCT idfk AS id, c, d FROM t2 WHERE idfk  = 1) AS y
    ON x.c = y.c AND x.d = y.d
 GROUP BY x.id
HAVING COUNT(*) = (SELECT COUNT(*)
                     FROM (SELECT DISTINCT idfk AS id, c, d FROM t2 WHERE idfk  = 1) AS x
                    GROUP BY id);

ROLLBACK;
