-- @(#)SO 33104874
-- @(#)Create US_States table

DROP TABLE IF EXISTS US_States;

CREATE TABLE US_States
(
    code    CHAR(2) NOT NULL PRIMARY KEY,
    name    VARCHAR(15) NOT NULL UNIQUE
);

