-- @(#)SO 3310-4874
-- @(#)Create states_starting function

DROP FUNCTION IF EXISTS states_starting;

CREATE FUNCTION states_starting(initial CHAR(1)) RETURNING VARCHAR(15);

    DEFINE result VARCHAR(15);

    FOREACH SELECT Name
              INTO result
              FROM US_States
              WHERE Code[1] = initial
              ORDER BY Name
        RETURN result WITH RESUME;
     END FOREACH;

END FUNCTION;

