SELECT DISTINCT table3.no_cev,   
            table1.literal,   
         table1.colid,   
         table2.repid,   
         table2.valor,   
         table2.indicador,   
         '',   
         '',   
         table2.origen,   
         table2.codi,  
        table2.no_cia,
        table2.num_dcca,
        table2.no_aprof,
        table2.no_compta
    FROM table1,   
         OUTER table2,   
         table3  
   WHERE ( table1.colid  = table2.colid) and  
         ( table1.grupid  = table2.grupid) and  
         ( table3.no_cev  = table2.no_cev) and  
         ( ( table1.grupid = 2) AND  
         ( table2.cod_exp = 99609 ) AND  
         ( table2.indicador = 'S' ) ) AND  
         ( table3.num_dcca = 1); 
         ( table3.codest = 76695);
