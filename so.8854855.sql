BEGIN;

CREATE TABLE Large_Table
(
    Event_Time  DATETIME YEAR TO MINUTE NOT NULL,
    User_ID     CHAR(15) NOT NULL,
    Other_Data  INTEGER NOT NULL,
    PRIMARY KEY(User_ID, Event_Time)
);

INSERT INTO Large_Table(Event_Time, User_ID, Other_Data) VALUES('2012-01-01 09:15', 'Alpha',  1) { R4 };
INSERT INTO Large_Table(Event_Time, User_ID, Other_Data) VALUES('2012-01-01 11:15', 'Alpha',  2) { R4 };
INSERT INTO Large_Table(Event_Time, User_ID, Other_Data) VALUES('2012-01-01 13:15', 'Alpha',  3) { R4 };
INSERT INTO Large_Table(Event_Time, User_ID, Other_Data) VALUES('2012-01-01 15:15', 'Alpha',  4) { R4 };
INSERT INTO Large_Table(Event_Time, User_ID, Other_Data) VALUES('2012-01-01 12:17', 'Beta',   1) { R4 };

INSERT INTO Large_Table(Event_Time, User_ID, Other_Data) VALUES('2012-01-02 09:15', 'Alpha',  5) { R1 };
INSERT INTO Large_Table(Event_Time, User_ID, Other_Data) VALUES('2012-01-02 10:17', 'Beta',   2) { R1 };

INSERT INTO Large_Table(Event_Time, User_ID, Other_Data) VALUES('2012-01-03 09:15', 'Alpha',  6) { R2 };
INSERT INTO Large_Table(Event_Time, User_ID, Other_Data) VALUES('2012-01-03 11:15', 'Alpha',  7) { R2 };
INSERT INTO Large_Table(Event_Time, User_ID, Other_Data) VALUES('2012-01-03 10:17', 'Beta',   3) { R1 };

INSERT INTO Large_Table(Event_Time, User_ID, Other_Data) VALUES('2012-01-04 09:15', 'Alpha',  8) { R3 };
INSERT INTO Large_Table(Event_Time, User_ID, Other_Data) VALUES('2012-01-04 11:15', 'Alpha',  9) { R3 };
INSERT INTO Large_Table(Event_Time, User_ID, Other_Data) VALUES('2012-01-04 13:15', 'Alpha', 10) { R3 };
INSERT INTO Large_Table(Event_Time, User_ID, Other_Data) VALUES('2012-01-04 10:17', 'Beta',   4) { R1 };

INSERT INTO Large_Table(Event_Time, User_ID, Other_Data) VALUES('2012-01-05 09:15', 'Alpha', 11) { R2 };
INSERT INTO Large_Table(Event_Time, User_ID, Other_Data) VALUES('2012-01-05 11:15', 'Alpha', 12) { R2 };
INSERT INTO Large_Table(Event_Time, User_ID, Other_Data) VALUES('2012-01-05 10:17', 'Beta',   5) { R1 };
{ Probe here }
INSERT INTO Large_Table(Event_Time, User_ID, Other_Data) VALUES('2012-01-05 15:15', 'Alpha', 13) { R2 };
INSERT INTO Large_Table(Event_Time, User_ID, Other_Data) VALUES('2012-01-05 17:15', 'Alpha', 14) { R2 };
INSERT INTO Large_Table(Event_Time, User_ID, Other_Data) VALUES('2012-01-05 16:17', 'Beta',   6) { R1 };

INSERT INTO Large_Table(Event_Time, User_ID, Other_Data) VALUES('2012-01-06 09:15', 'Alpha', 15) { R6 };
INSERT INTO Large_Table(Event_Time, User_ID, Other_Data) VALUES('2012-01-06 11:15', 'Alpha', 16) { R6 };
INSERT INTO Large_Table(Event_Time, User_ID, Other_Data) VALUES('2012-01-06 13:15', 'Alpha', 17) { R6 };
INSERT INTO Large_Table(Event_Time, User_ID, Other_Data) VALUES('2012-01-06 15:15', 'Alpha', 18) { R6 };
INSERT INTO Large_Table(Event_Time, User_ID, Other_Data) VALUES('2012-01-06 17:15', 'Alpha', 19) { R6 };
INSERT INTO Large_Table(Event_Time, User_ID, Other_Data) VALUES('2012-01-06 19:15', 'Alpha', 20) { R6 };
INSERT INTO Large_Table(Event_Time, User_ID, Other_Data) VALUES('2012-01-06 16:17', 'Beta',   7) { R1 };

INSERT INTO Large_Table(Event_Time, User_ID, Other_Data) VALUES('2012-01-07 09:15', 'Alpha', 21) { R1 };
INSERT INTO Large_Table(Event_Time, User_ID, Other_Data) VALUES('2012-01-07 11:17', 'Beta',   8) { R1 };
INSERT INTO Large_Table(Event_Time, User_ID, Other_Data) VALUES('2012-01-07 12:15', 'Alpha', 22) { R1 };
INSERT INTO Large_Table(Event_Time, User_ID, Other_Data) VALUES('2012-01-07 13:17', 'Beta',   9) { R1 };

INSERT INTO Large_Table(Event_Time, User_ID, Other_Data) VALUES('2012-01-08 09:15', 'Alpha', 23) { R5 };
INSERT INTO Large_Table(Event_Time, User_ID, Other_Data) VALUES('2012-01-08 11:15', 'Alpha', 24) { R5 };
INSERT INTO Large_Table(Event_Time, User_ID, Other_Data) VALUES('2012-01-08 13:15', 'Alpha', 25) { R5 };
INSERT INTO Large_Table(Event_Time, User_ID, Other_Data) VALUES('2012-01-08 15:15', 'Alpha', 26) { R5 };
INSERT INTO Large_Table(Event_Time, User_ID, Other_Data) VALUES('2012-01-08 17:15', 'Alpha', 27) { R5 };

CREATE TABLE Small_Table
(
    Event_Time  DATETIME YEAR TO MINUTE NOT NULL,
    User_ID     CHAR(15) NOT NULL,
    Other_Data  INTEGER NOT NULL,
    PRIMARY KEY(User_ID, Event_Time)
);

INSERT INTO Small_Table(Event_Time, User_ID, Other_Data) VALUES('2012-01-01 06:15', 'Alpha', 131) { XX };
INSERT INTO Small_Table(Event_Time, User_ID, Other_Data) VALUES('2012-01-01 06:20', 'Alpha',  31) { YY };
INSERT INTO Small_Table(Event_Time, User_ID, Other_Data) VALUES('2012-01-01 10:20', 'Alpha',  32) { YY };
INSERT INTO Small_Table(Event_Time, User_ID, Other_Data) VALUES('2012-01-01 13:20', 'Alpha',  33) { YY };
INSERT INTO Small_Table(Event_Time, User_ID, Other_Data) VALUES('2012-01-01 15:20', 'Alpha',  34) { YY };
INSERT INTO Small_Table(Event_Time, User_ID, Other_Data) VALUES('2012-01-01 18:15', 'Alpha', 134) { XX };

INSERT INTO Small_Table(Event_Time, User_ID, Other_Data) VALUES('2012-01-02 06:15', 'Alpha', 135) { XX };
INSERT INTO Small_Table(Event_Time, User_ID, Other_Data) VALUES('2012-01-02 06:16', 'Alpha',  35) { YY };
INSERT INTO Small_Table(Event_Time, User_ID, Other_Data) VALUES('2012-01-02 10:20', 'Alpha',  35) { YY };
INSERT INTO Small_Table(Event_Time, User_ID, Other_Data) VALUES('2012-01-02 12:14', 'Alpha',  35) { YY };
INSERT INTO Small_Table(Event_Time, User_ID, Other_Data) VALUES('2012-01-02 12:15', 'Alpha', 135) { XX };

INSERT INTO Small_Table(Event_Time, User_ID, Other_Data) VALUES('2012-01-03 09:20', 'Alpha',  36) { YY };
INSERT INTO Small_Table(Event_Time, User_ID, Other_Data) VALUES('2012-01-03 11:20', 'Alpha',  37) { YY };

INSERT INTO Small_Table(Event_Time, User_ID, Other_Data) VALUES('2012-01-04 09:20', 'Alpha',  38) { YY };
INSERT INTO Small_Table(Event_Time, User_ID, Other_Data) VALUES('2012-01-04 11:20', 'Alpha',  39) { YY };
INSERT INTO Small_Table(Event_Time, User_ID, Other_Data) VALUES('2012-01-04 13:20', 'Alpha',  40) { YY };

INSERT INTO Small_Table(Event_Time, User_ID, Other_Data) VALUES('2012-01-05 09:20', 'Alpha',  41) { YY };
INSERT INTO Small_Table(Event_Time, User_ID, Other_Data) VALUES('2012-01-05 11:20', 'Alpha',  42) { YY };
INSERT INTO Small_Table(Event_Time, User_ID, Other_Data) VALUES('2012-01-05 13:20', 'Alpha',  42) { 22 };
INSERT INTO Small_Table(Event_Time, User_ID, Other_Data) VALUES('2012-01-05 15:20', 'Alpha',  43) { YY };
INSERT INTO Small_Table(Event_Time, User_ID, Other_Data) VALUES('2012-01-05 17:20', 'Alpha',  44) { YY };

INSERT INTO Small_Table(Event_Time, User_ID, Other_Data) VALUES('2012-01-06 09:20', 'Alpha',  45) { YY };
INSERT INTO Small_Table(Event_Time, User_ID, Other_Data) VALUES('2012-01-06 11:20', 'Alpha',  46) { YY };
INSERT INTO Small_Table(Event_Time, User_ID, Other_Data) VALUES('2012-01-06 13:20', 'Alpha',  47) { YY };
INSERT INTO Small_Table(Event_Time, User_ID, Other_Data) VALUES('2012-01-06 15:20', 'Alpha',  48) { YY };
INSERT INTO Small_Table(Event_Time, User_ID, Other_Data) VALUES('2012-01-06 17:20', 'Alpha',  49) { YY };
INSERT INTO Small_Table(Event_Time, User_ID, Other_Data) VALUES('2012-01-06 19:20', 'Alpha',  50) { YY };

INSERT INTO Small_Table(Event_Time, User_ID, Other_Data) VALUES('2012-01-07 09:20', 'Alpha',  51) { YY };
INSERT INTO Small_Table(Event_Time, User_ID, Other_Data) VALUES('2012-01-07 10:20', 'Alpha',  51) { 22 };
INSERT INTO Small_Table(Event_Time, User_ID, Other_Data) VALUES('2012-01-07 12:20', 'Alpha',  52) { YY };

INSERT INTO Small_Table(Event_Time, User_ID, Other_Data) VALUES('2012-01-08 09:20', 'Alpha',  53) { YY };
INSERT INTO Small_Table(Event_Time, User_ID, Other_Data) VALUES('2012-01-08 11:20', 'Alpha',  54) { YY };
INSERT INTO Small_Table(Event_Time, User_ID, Other_Data) VALUES('2012-01-08 13:20', 'Alpha',  55) { YY };
INSERT INTO Small_Table(Event_Time, User_ID, Other_Data) VALUES('2012-01-08 15:20', 'Alpha',  56) { YY };
INSERT INTO Small_Table(Event_Time, User_ID, Other_Data) VALUES('2012-01-08 17:20', 'Alpha',  57) { YY };

INSERT INTO Small_Table(Event_Time, User_ID, Other_Data) VALUES('2012-01-07 13:27', 'Beta',   9) { R1 };
INSERT INTO Small_Table(Event_Time, User_ID, Other_Data) VALUES('2012-01-07 11:27', 'Beta',   8) { R1 };
INSERT INTO Small_Table(Event_Time, User_ID, Other_Data) VALUES('2012-01-06 16:27', 'Beta',   7) { R1 };
INSERT INTO Small_Table(Event_Time, User_ID, Other_Data) VALUES('2012-01-05 16:27', 'Beta',   6) { R1 };
INSERT INTO Small_Table(Event_Time, User_ID, Other_Data) VALUES('2012-01-05 10:27', 'Beta',   5) { R1 };
INSERT INTO Small_Table(Event_Time, User_ID, Other_Data) VALUES('2012-01-04 10:27', 'Beta',   4) { R1 };
INSERT INTO Small_Table(Event_Time, User_ID, Other_Data) VALUES('2012-01-03 10:27', 'Beta',   3) { R1 };
INSERT INTO Small_Table(Event_Time, User_ID, Other_Data) VALUES('2012-01-02 10:27', 'Beta',   2) { R1 };
INSERT INTO Small_Table(Event_Time, User_ID, Other_Data) VALUES('2012-01-01 12:27', 'Beta',   1) { R4 };

echo "Large Table Data";
SELECT * FROM Large_Table ORDER BY User_ID, Event_Time;

-- trace on;

echo "Singleton ranges";

    -- Ranges of exactly 1 event
    SELECT lt1.user_id, lt1.event_time AS min_time, lt1.event_time AS max_time
      FROM Large_Table AS lt1
     WHERE NOT EXISTS -- an earlier event that is close enough
           (SELECT *
              FROM Large_Table AS lt3
             WHERE lt1.user_id = lt3.user_id
               AND lt3.event_time > lt1.event_time - 3 UNITS HOUR
               AND lt3.event_time < lt1.event_time
           )
       AND NOT EXISTS -- a later event that is close enough
           (SELECT *
              FROM Large_Table AS lt4
             WHERE lt1.user_id = lt4.user_id
               AND lt4.event_time > lt1.event_time
               AND lt4.event_time < lt1.event_time + 3 UNITS HOUR
           )
    ORDER BY User_ID, Min_Time;

echo "Doubleton Ranges";

    -- Ranges of exactly 2 events
    SELECT lt1.user_id, lt1.event_time AS min_time, lt2.event_time AS max_time
      FROM Large_Table AS lt1
      JOIN Large_Table AS lt2
        ON lt1.user_id = lt2.user_id
       AND lt1.event_time < lt2.event_time
       AND lt2.event_time < lt1.event_time + 3 UNITS HOUR
     WHERE NOT EXISTS -- an earlier event that is close enough
           (SELECT *
              FROM Large_Table AS lt3
             WHERE lt1.user_id = lt3.user_id
               AND lt3.event_time > lt1.event_time - 3 UNITS HOUR
               AND lt3.event_time < lt1.event_time
           )
       AND NOT EXISTS -- a later event that is close enough
           (SELECT *
              FROM Large_Table AS lt4
             WHERE lt1.user_id = lt4.user_id
               AND lt4.event_time > lt2.event_time
               AND lt4.event_time < lt2.event_time + 3 UNITS HOUR
           )
       AND NOT EXISTS -- any event in between
           (SELECT *
              FROM Large_Table AS lt5
             WHERE lt1.user_id = lt5.user_id
               AND lt5.event_time > lt1.event_time
               AND lt5.event_time < lt2.event_time
           )
    ORDER BY User_ID, Min_Time;

echo "Multiple Event Ranges";

    -- Ranges of 3 or more events
    SELECT lt1.user_id, lt1.event_time AS min_time, lt2.event_time AS max_time
      FROM Large_Table AS lt1
      JOIN Large_Table AS lt2
        ON lt1.user_id = lt2.user_id
       AND lt1.event_time < lt2.event_time
     WHERE NOT EXISTS -- an earlier event that is close enough
           (SELECT *
              FROM Large_Table AS lt3
             WHERE lt1.user_id = lt3.user_id
               AND lt3.event_time > lt1.event_time - 3 UNITS HOUR
               AND lt3.event_time < lt1.event_time
           )
       AND NOT EXISTS -- a later event that is close enough
           (SELECT *
              FROM Large_Table AS lt4
             WHERE lt1.user_id = lt4.user_id
               AND lt4.event_time > lt2.event_time
               AND lt4.event_time < lt2.event_time + 3 UNITS HOUR
           )
       AND NOT EXISTS -- a gap that's too big in the events between first and last
           (SELECT *
              FROM Large_Table AS lt5 -- E5 before E6
              JOIN Large_Table AS lt6
                ON lt5.user_id = lt6.user_id
               AND lt5.event_time < lt6.event_time
             WHERE lt1.user_id = lt5.user_id
               AND lt6.event_time < lt2.event_time
               AND lt5.event_time > lt1.event_time
               AND (lt6.event_time - lt5.event_time) > 3 UNITS HOUR
               AND NOT EXISTS -- an event in between these two
                   (SELECT *
                      FROM Large_Table AS lt9
                     WHERE lt5.user_id = lt9.user_id
                       AND lt9.event_time > lt5.event_time
                       AND lt9.event_time < lt6.event_time
                   )
           )
       AND EXISTS -- an event close enough after the start
           (SELECT *
              FROM Large_Table AS lt7
             WHERE lt1.user_id = lt7.user_id
               AND lt1.event_time < lt7.event_time
               AND lt7.event_time < lt1.event_time + 3 UNITS HOUR
               AND lt7.event_time < lt2.event_time
           )
       AND EXISTS -- an event close enough before the end
           (SELECT *
              FROM Large_Table AS lt8
             WHERE lt2.user_id = lt8.user_id
               AND lt2.event_time > lt8.event_time
               AND lt8.event_time > lt2.event_time - 3 UNITS HOUR
               AND lt8.event_time > lt1.event_time
           )
    ORDER BY User_ID, Min_Time;

echo "All Ranges in Large Table";

    -- Ranges of exactly 1 event
    SELECT lt1.user_id, lt1.event_time AS min_time, lt1.event_time AS max_time
      FROM Large_Table AS lt1
     WHERE NOT EXISTS -- an earlier event that is close enough
           (SELECT *
              FROM Large_Table AS lt3
             WHERE lt1.user_id = lt3.user_id
               AND lt3.event_time > lt1.event_time - 3 UNITS HOUR
               AND lt3.event_time < lt1.event_time
           )
       AND NOT EXISTS -- a later event that is close enough
           (SELECT *
              FROM Large_Table AS lt4
             WHERE lt1.user_id = lt4.user_id
               AND lt4.event_time > lt1.event_time
               AND lt4.event_time < lt1.event_time + 3 UNITS HOUR
           )

    UNION

    -- Ranges of exactly 2 events
    SELECT lt1.user_id, lt1.event_time AS min_time, lt2.event_time AS max_time
      FROM Large_Table AS lt1
      JOIN Large_Table AS lt2
        ON lt1.user_id = lt2.user_id
       AND lt1.event_time < lt2.event_time
       AND lt2.event_time < lt1.event_time + 3 UNITS HOUR
     WHERE NOT EXISTS -- an earlier event that is close enough
           (SELECT *
              FROM Large_Table AS lt3
             WHERE lt1.user_id = lt3.user_id
               AND lt3.event_time > lt1.event_time - 3 UNITS HOUR
               AND lt3.event_time < lt1.event_time
           )
       AND NOT EXISTS -- a later event that is close enough
           (SELECT *
              FROM Large_Table AS lt4
             WHERE lt1.user_id = lt4.user_id
               AND lt4.event_time > lt2.event_time
               AND lt4.event_time < lt2.event_time + 3 UNITS HOUR
           )
       AND NOT EXISTS -- any event in between
           (SELECT *
              FROM Large_Table AS lt5
             WHERE lt1.user_id = lt5.user_id
               AND lt5.event_time > lt1.event_time
               AND lt5.event_time < lt2.event_time
           )

    UNION

    -- Ranges of 3 or more events
    SELECT lt1.user_id, lt1.event_time AS min_time, lt2.event_time AS max_time
      FROM Large_Table AS lt1
      JOIN Large_Table AS lt2
        ON lt1.user_id = lt2.user_id
       AND lt1.event_time < lt2.event_time
     WHERE NOT EXISTS -- an earlier event that is close enough
           (SELECT *
              FROM Large_Table AS lt3
             WHERE lt1.user_id = lt3.user_id
               AND lt3.event_time > lt1.event_time - 3 UNITS HOUR
               AND lt3.event_time < lt1.event_time
           )
       AND NOT EXISTS -- a later event that is close enough
           (SELECT *
              FROM Large_Table AS lt4
             WHERE lt1.user_id = lt4.user_id
               AND lt4.event_time > lt2.event_time
               AND lt4.event_time < lt2.event_time + 3 UNITS HOUR
           )
       AND NOT EXISTS -- a gap that's too big in the events between first and last
           (SELECT *
              FROM Large_Table AS lt5 -- E5 before E6
              JOIN Large_Table AS lt6
                ON lt5.user_id = lt6.user_id
               AND lt5.event_time < lt6.event_time
             WHERE lt1.user_id = lt5.user_id
               AND lt6.event_time < lt2.event_time
               AND lt5.event_time > lt1.event_time
               AND (lt6.event_time - lt5.event_time) > 3 UNITS HOUR
               AND NOT EXISTS -- an event in between these two
                   (SELECT *
                      FROM Large_Table AS lt9
                     WHERE lt5.user_id = lt9.user_id
                       AND lt9.event_time > lt5.event_time
                       AND lt9.event_time < lt6.event_time
                   )
           )
       AND EXISTS -- an event close enough after the start
           (SELECT *
              FROM Large_Table AS lt7
             WHERE lt1.user_id = lt7.user_id
               AND lt1.event_time < lt7.event_time
               AND lt7.event_time < lt1.event_time + 3 UNITS HOUR
               AND lt7.event_time < lt2.event_time
           )
       AND EXISTS -- an event close enough before the end
           (SELECT *
              FROM Large_Table AS lt8
             WHERE lt2.user_id = lt8.user_id
               AND lt2.event_time > lt8.event_time
               AND lt8.event_time > lt2.event_time - 3 UNITS HOUR
               AND lt8.event_time > lt1.event_time
           )

    ORDER BY User_ID, Min_Time;

echo "Small Table Data";
SELECT * FROM Small_Table ORDER BY User_ID, Event_Time;

echo "Final Query";

format fixsep;
delim '\t';

    SELECT S.User_id, S.Event_Time, L.Min_Time, L.Max_Time, S.Other_Data
      FROM Small_Table AS S
      JOIN (
            -- Ranges of exactly 1 event
            SELECT lt1.user_id, lt1.event_time AS min_time, lt1.event_time AS max_time
              FROM Large_Table AS lt1
             WHERE NOT EXISTS -- an earlier event that is close enough
                   (SELECT *
                      FROM Large_Table AS lt3
                     WHERE lt1.user_id = lt3.user_id
                       AND lt3.event_time > lt1.event_time - 3 UNITS HOUR
                       AND lt3.event_time < lt1.event_time
                   )
               AND NOT EXISTS -- a later event that is close enough
                   (SELECT *
                      FROM Large_Table AS lt4
                     WHERE lt1.user_id = lt4.user_id
                       AND lt4.event_time > lt1.event_time
                       AND lt4.event_time < lt1.event_time + 3 UNITS HOUR
                   )
            UNION
            -- Ranges of exactly 2 events
            SELECT lt1.user_id, lt1.event_time AS min_time, lt2.event_time AS max_time
              FROM Large_Table AS lt1
              JOIN Large_Table AS lt2
                ON lt1.user_id = lt2.user_id
               AND lt1.event_time < lt2.event_time
               AND lt2.event_time < lt1.event_time + 3 UNITS HOUR
             WHERE NOT EXISTS -- an earlier event that is close enough
                   (SELECT *
                      FROM Large_Table AS lt3
                     WHERE lt1.user_id = lt3.user_id
                       AND lt3.event_time > lt1.event_time - 3 UNITS HOUR
                       AND lt3.event_time < lt1.event_time
                   )
               AND NOT EXISTS -- a later event that is close enough
                   (SELECT *
                      FROM Large_Table AS lt4
                     WHERE lt1.user_id = lt4.user_id
                       AND lt4.event_time > lt2.event_time
                       AND lt4.event_time < lt2.event_time + 3 UNITS HOUR
                   )
               AND NOT EXISTS -- any event in between
                   (SELECT *
                      FROM Large_Table AS lt5
                     WHERE lt1.user_id = lt5.user_id
                       AND lt5.event_time > lt1.event_time
                       AND lt5.event_time < lt2.event_time
                   )
            UNION
            -- Ranges of 3 or more events
            SELECT lt1.user_id, lt1.event_time AS min_time, lt2.event_time AS max_time
              FROM Large_Table AS lt1
              JOIN Large_Table AS lt2
                ON lt1.user_id = lt2.user_id
               AND lt1.event_time < lt2.event_time
             WHERE NOT EXISTS -- an earlier event that is close enough
                   (SELECT *
                      FROM Large_Table AS lt3
                     WHERE lt1.user_id = lt3.user_id
                       AND lt3.event_time > lt1.event_time - 3 UNITS HOUR
                       AND lt3.event_time < lt1.event_time
                   )
               AND NOT EXISTS -- a later event that is close enough
                   (SELECT *
                      FROM Large_Table AS lt4
                     WHERE lt1.user_id = lt4.user_id
                       AND lt4.event_time > lt2.event_time
                       AND lt4.event_time < lt2.event_time + 3 UNITS HOUR
                   )
               AND NOT EXISTS -- a gap that's too big in the events between first and last
                   (SELECT *
                      FROM Large_Table AS lt5 -- E5 before E6
                      JOIN Large_Table AS lt6
                        ON lt5.user_id = lt6.user_id
                       AND lt5.event_time < lt6.event_time
                     WHERE lt1.user_id = lt5.user_id
                       AND lt6.event_time < lt2.event_time
                       AND lt5.event_time > lt1.event_time
                       AND (lt6.event_time - lt5.event_time) > 3 UNITS HOUR
                       AND NOT EXISTS -- an event in between these two
                           (SELECT *
                              FROM Large_Table AS lt9
                             WHERE lt5.user_id = lt9.user_id
                               AND lt9.event_time > lt5.event_time
                               AND lt9.event_time < lt6.event_time
                           )
                   )
               AND EXISTS -- an event close enough after the start
                   (SELECT *
                      FROM Large_Table AS lt7
                     WHERE lt1.user_id = lt7.user_id
                       AND lt1.event_time < lt7.event_time
                       AND lt7.event_time < lt1.event_time + 3 UNITS HOUR
                       AND lt7.event_time < lt2.event_time
                   )
               AND EXISTS -- an event close enough before the end
                   (SELECT *
                      FROM Large_Table AS lt8
                     WHERE lt2.user_id = lt8.user_id
                       AND lt2.event_time > lt8.event_time
                       AND lt8.event_time > lt2.event_time - 3 UNITS HOUR
                       AND lt8.event_time > lt1.event_time
                   )
           ) AS L
        ON S.User_ID = L.User_ID
     WHERE S.Event_Time > L.Min_Time - 3 UNITS HOUR
       AND S.Event_Time < L.Max_Time + 3 UNITS HOUR
    ORDER BY User_ID, Event_Time, Min_Time;

echo "Postulated alternative";

SELECT lt1.user_id, lt1.event_time AS min_time, lt2.event_time AS max_time
  FROM Large_Table AS lt1
  JOIN Large_Table AS lt2
    ON lt1.user_id = lt2.user_id
   AND lt1.event_time < lt2.event_time
 WHERE NOT EXISTS -- an earlier event that is close enough
       (SELECT *
          FROM Large_Table AS lt3
         WHERE lt1.user_id = lt3.user_id
           AND lt3.event_time > lt1.event_time - 3 UNITS HOUR
           AND lt3.event_time < lt1.event_time
       )
   AND NOT EXISTS -- a later event that is close enough
       (SELECT *
          FROM Large_Table AS lt4
         WHERE lt1.user_id = lt4.user_id
           AND lt4.event_time > lt2.event_time
           AND lt4.event_time < lt2.event_time + 3 UNITS HOUR
       )
   AND NOT EXISTS -- a gap that's too big in the events between first and last
       (SELECT *
          FROM Large_Table AS lt5 -- E5 before E6
          JOIN Large_Table AS lt6
            ON lt5.user_id = lt6.user_id
           AND lt1.user_id = lt5.user_id
           AND lt5.event_time < lt6.event_time
           AND lt6.event_time <= lt2.event_time
           AND lt5.event_time >= lt1.event_time
           AND (lt6.event_time - lt5.event_time) > 3 UNITS HOUR
           AND NOT EXISTS
               (SELECT *
                  FROM large_table AS lt9
                 WHERE lt9.event_time > lt5.event_time
                   AND lt6.event_time > lt9.event_time
               )
       )
ORDER BY User_ID, Min_Time;

ROLLBACK;
