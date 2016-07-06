SELECT employee_id, manager_id
  FROM empl_relation
 START WITH employee_id =
                (SELECT employee_id
                   FROM empl_relation AS er
                  WHERE er.manager_id IS NULL
                  START WITH employee_id = 5150
                CONNECT BY employee_id = PRIOR manager_id
                )
CONNECT BY PRIOR employee_id = manager_id
 ORDER BY employee_id;
