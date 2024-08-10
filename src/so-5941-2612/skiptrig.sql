DROP TABLE IF EXISTS trigger_test;
CREATE TABLE trigger_test
(
    s   SERIAL NOT NULL PRIMARY KEY,
    t   DATETIME YEAR TO SECOND NOT NULL DEFAULT CURRENT YEAR TO SECOND,
    v   VARCHAR(64) NOT NULL
);

DROP TABLE IF EXISTS trigger_log;
CREATE TABLE trigger_log
(
    log_id  SERIAL NOT NULL PRIMARY KEY,
    old_s   INTEGER NOT NULL,
    old_t   DATETIME YEAR TO SECOND NOT NULL,
    new_t   DATETIME YEAR TO SECOND NOT NULL,
    old_v   VARCHAR(64) NOT NULL,
    new_v   VARCHAR(64) NOT NULL,
    log_t   DATETIME YEAR TO SECOND NOT NULL DEFAULT CURRENT YEAR TO SECOND,
    log_u   VARCHAR(32) NOT NULL DEFAULT USER
);

CREATE TRIGGER skip_user
    UPDATE ON trigger_test
    REFERENCING OLD AS OLD NEW AS NEW
    FOR EACH ROW WHEN(USER != 'informix')
    (INSERT INTO trigger_log(old_s, old_t, new_t, old_v, new_v)
        VALUES(old.s, old.t, new.t, old.v, new.v)
    )
    ;
