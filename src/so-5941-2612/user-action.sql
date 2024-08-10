INSERT INTO trigger_test(v) VALUES("Hello");
SELECT * FROM trigger_test;
SELECT * FROM trigger_log;
UPDATE trigger_test SET t = '2019-12-31 23:59:59', v = 'Farewell to 2019';
SELECT * FROM trigger_test;
SELECT * FROM trigger_log;
UPDATE trigger_test SET t = '2038-01-19 03:14:07', v = 'Farewell to 32-bit Unix time';
SELECT * FROM trigger_test;
SELECT * FROM trigger_log;
