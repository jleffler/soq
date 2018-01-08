### Stack Overflow Question 4389-1911

[SO 4389-1911](https://stackoverflow.com/q/43891911) &mdash;
How to check only the first value of the row returned from stored procedure in a SQL query

### The question

If I have a stored procedure like this:

    get_my_dep(empNum)

and it returns one row ex:

    call get_my_dep(567);

    dep_code  dep_year  dep_name
    66        2017       HR

How to check only the first value of the row (`dep_code`) in my query like this:

    SELECT * 
    FROM rmcandidate a INNER JOIN task b
    ON a.task_code = b.task_code
    WHERE get_my_dep(emp_num) != 0 --here I want to check only the dep_code
    AND b.active_flag =1

### The answer

The answer was produced by [Simon
Riddle](https://stackoverflow.com/users/7630698/simon-riddle); I had
nothing to do with it.

The script was my conconction based on Simon's answer.

