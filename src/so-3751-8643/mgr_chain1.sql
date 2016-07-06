{ SO 37518643 }
SELECT employee_id, manager_id
    FROM empl_relation  
    START WITH employee_id = 5148 
    CONNECT BY PRIOR employee_id = manager_id 
    ORDER  SIBLINGS BY employee_id;
