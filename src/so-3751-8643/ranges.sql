TRACE ON;
BEGIN;
CREATE TABLE sequence (id INTEGER NOT NULL PRIMARY KEY);

INSERT INTO sequence VALUES(1);
INSERT INTO sequence VALUES(2);
INSERT INTO sequence VALUES(3);
INSERT INTO sequence VALUES(4);
INSERT INTO sequence VALUES(6);
INSERT INTO sequence VALUES(8);
INSERT INTO sequence VALUES(9);
INSERT INTO sequence VALUES(10);
INSERT INTO sequence VALUES(15);
INSERT INTO sequence VALUES(16);
INSERT INTO sequence VALUES(17);
INSERT INTO sequence VALUES(18);
INSERT INTO sequence VALUES(19);
INSERT INTO sequence VALUES(20);

SELECT l.id
  FROM sequence AS l
  LEFT OUTER JOIN sequence AS r ON r.id = l.id - 1
 WHERE r.id IS NULL;

SELECT l.id
  FROM sequence AS l
  LEFT OUTER JOIN sequence AS r ON r.id = l.id + 1
 WHERE r.id IS NULL;

SELECT l.id AS START,
       (SELECT MIN(a.id) AS id
          FROM sequence AS a
          LEFT OUTER JOIN sequence AS b ON a.id = b.id - 1
         WHERE b.id IS NULL
           AND a.id >= l.id
       ) AS END
  FROM sequence AS l
  LEFT OUTER JOIN sequence AS r ON r.id = l.id - 1
 WHERE r.id IS NULL;

ROLLBACK;
