SELECT DISTINCT
       t3.no_cev,   
       --t1.literal,   
       --t1.colid,   
       t2.repid,   
       t2.valor,   
       t2.indicador,   
       --t2.origen,   
       --t2.codi,  
       --t2.no_cia,
       --t2.num_dcca,
       --t2.no_aprof,
       --t2.no_compta
       "Junk"
  FROM  --    table1 AS t1
 --INNER JOIN table3 AS t3 ON 1 = 1
            table3 AS t3
 OUTER JOIN table2 AS t2 ON t3.no_cev = t2.no_cev
                        --AND t1.colid = t2.colid
                        --t1.colid = t2.colid
                        --AND t1.grupid = t2.grupid
                        --t1.grupid = t2.grupid
 WHERE --t1.grupid = 2
   t2.cod_exp = 99609
   --AND t2.cod_exp = 99609
   AND t2.indicador = 'S'
   AND t3.num_dcca = 1
   AND t3.codest = 76695;
