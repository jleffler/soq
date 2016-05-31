{ SO 37518643 }
SELECT employee_id, manager_id
  FROM empl_relation
 START WITH employee_id = (
                    SELECT h.employee_id
                      FROM (SELECT employee_id, manager_id
                              FROM empl_relation
                             START WITH employee_id = 5150 
                           CONNECT BY employee_id = PRIOR manager_id 
                           ) AS h
                     WHERE h.manager_id IS NULL)
CONNECT BY PRIOR employee_id = manager_id 
 ORDER BY employee_id;
