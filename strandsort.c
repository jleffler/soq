/*
** Pseudocode for Strand Sort
** From: http://forum.vingrad.ru/forum/s/3958890c51aa1e8dec147e153b8ebf77/topic-280157/anchor-entry2022456/0.html
** Via:  http://stackoverflow.com/questions/3644115/strand-sort-implementation-closed
**
**  procedure strandSort( A : list of sortable items ) defined as:
**    while length( A ) > 0
**      clear sublist
**      sublist[ 0 ] := A[ 0 ]
**      remove A[ 0 ]
**      for each i in 0 to length( A ) do:
**        if A[ i ] > sublist[ last ] then
**          append A[ i ] to sublist
**          remove A[ i ]
**        end if
**      end for
**      merge sublist into results
**    end while
**    return results
**  end procedure
**
** It is not clear how well this can work for array based data - though
** it is clear how it works for lists.  An already sorted list will be
** processed in a single pass for O(N) best-case performance.  A reverse
** sorted list will require N iterations through the data, removing just
** the first item each time, leading to an O(N-squared) performance.
** With lists, you only need 3 auxilliary lists - which might be fairly
** efficient.
**
** With arrays, we need an array of size N for the sub-list, and another
** array of size N for the results.  I suppose that really clever
** programming could do without more than that (by observing that there
** is space in the results array for the sub-list) but the 'obvious'
** solution needs to merge results1 with sublist into results2, so that
** the algorithm needs 4N space (input array, sublist, results1,
** results2).
*/



