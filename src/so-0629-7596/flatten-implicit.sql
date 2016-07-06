BEGIN;

CREATE TABLE Anonymous
(
     Name        VARCHAR(25),
     Value       INTEGER,
     Predecessor VARCHAR(25)
);

INSERT INTO Anonymous VALUES("buyingredients", 10, NULL);
INSERT INTO Anonymous VALUES("eat", 3, "cook");
INSERT INTO Anonymous VALUES("cook", 12, "mixingredients");
INSERT INTO Anonymous VALUES("mixingredients", 5, "buyingredients");

SET DEBUG FILE TO "debug.out";

CREATE PROCEDURE Flatten_Anonymous()

    DEFINE old_count INTEGER;
    DEFINE new_count INTEGER;
    TRACE ON;

    CREATE TEMP TABLE Flattened
    (
        Hierarchy   SERIAL,
        Level       INTEGER,
        Name        VARCHAR(25),
        Value       INTEGER,
        Predecessor VARCHAR(25)
    );

    CREATE TEMP TABLE Intermediate
    (
        Hierarchy   SERIAL,
        Level       INTEGER,
        Name        VARCHAR(25),
        Value       INTEGER,
        Predecessor VARCHAR(25)
    );

    INSERT INTO Flattened(Hierarchy, Level, Name, Value, Predecessor)
       SELECT 0, 0, name, value, predecessor
         FROM Anonymous
        WHERE Predecessor IS NULL;

    SELECT COUNT(*) INTO new_count FROM Flattened;
    LET old_count = new_count - 1;
    WHILE old_count != new_count
        INSERT INTO Intermediate(Hierarchy, Level, Name, Value, Predecessor)
            SELECT F.Hierarchy, F.Level + 1, A.Name, A.Value, A.Predecessor
              FROM Flattened AS F, Anonymous AS A
             WHERE F.Name = A.Predecessor
               AND F.Level = (SELECT MAX(Level) FROM Flattened);
        INSERT INTO Flattened SELECT * FROM Intermediate;
        DELETE FROM Intermediate;
        LET old_count = new_count;
        SELECT COUNT(*) INTO new_count FROM Flattened;
    END WHILE

    DROP TABLE Intermediate;

END PROCEDURE;

EXECUTE PROCEDURE Flatten_Anonymous();

SELECT Name, Value, Predecessor
  FROM Flattened
 ORDER BY Hierarchy, Level, Name;

DROP TABLE Flattened;

ROLLBACK;
