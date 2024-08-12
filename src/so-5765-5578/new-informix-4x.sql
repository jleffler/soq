SELECT DISTINCT
       t3.no_cev,   
       t2.repid,   
       t2.valor,   
       t2.indicador,   
       "Junk"
  FROM table3 AS t3
 --JOIN table2 AS t2 ON t3.no_cev = t2.no_cev {OK}
 LEFT JOIN table2 AS t2 ON t3.no_cev = t2.no_cev
 --WHERE t2.cod_exp = 99609
   --AND t2.indicador = 'S'
   --AND t3.num_dcca = 1
   --AND t3.codest = 76695;
