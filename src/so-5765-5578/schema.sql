DROP TABLE IF EXISTS table1;
DROP TABLE IF EXISTS table2;
DROP TABLE IF EXISTS table3;

CREATE TABLE table1
(
    grupid      INTEGER NOT NULL,       -- 2
    literal     VARCHAR(32) NOT NULL,
    colid       INTEGER NOT NULL
);

CREATE TABLE table2
(
    grupid      INTEGER NOT NULL,
    no_cev      INTEGER NOT NULL,
    colid       INTEGER NOT NULL,
    repid       INTEGER NOT NULL,
    valor       INTEGER NOT NULL,
    indicador   CHAR(1) NOT NULL,       -- 'S'
    origen      INTEGER NOT NULL,
    codi        INTEGER NOT NULL,
    no_cia      INTEGER NOT NULL,
    num_dcca    INTEGER NOT NULL,
    no_aprof    INTEGER NOT NULL,
    no_compta   INTEGER NOT NULL,
    cod_exp     INTEGER NOT NULL        -- 99609
);

CREATE TABLE table3
(
    no_cev      INTEGER NOT NULL,
    num_dcca    INTEGER NOT NULL,       -- 1
    codest      INTEGER NOT NULL        -- 76695
);

LOAD FROM "table1.unl" INSERT INTO table1;
LOAD FROM "table2.unl" INSERT INTO table2;
LOAD FROM "table3.unl" INSERT INTO table3;
