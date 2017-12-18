For this problem, it seems to me that you need to get three elements:

the current node (root)
the list for the left-child
the list for the right-child

And the resulting list needs to be:
    current node followed by
    list for left-child followed by
    list for right-child


Given the tree from the question:

          4                               
        /   \       
       2      6    ---------> output of DLL: 4<->2<->1<->3<->6<->5<->7.         
     /  \     / \                         
    1    3   5   7       

The final result is:
    node 4, followed by the list from node 2, followed by the list from node 6.

Of course, the list from node 2 is:
    node 2, followed by the list from node 1, followed by the list from node 3.
And the lists from node 1 and node 3 are trivial, so the result is:
    node 2, node 1, node 3
And similarly the list from node 6 is:
    node 6, followed by the list from node 5, followed by the list from node 7.
And the lists from node 5 and node 7 are trivial, so the result is:
    node 6, node 5, node 7
And hence the final result is:
    node 4, node 2, node 1, node 3, node 6, node 5, node 7

The lists are doubly-linked and null-terminated.  That means that on return to
the invocation processing node 4, the left list has the organization:

          +--------+     +--------+     +--------+
   0 <----|        |<----|        |<----|        |
          | Node 2 |     | Node 1 |     | Node 3 |
          |        |---->|        |---->|        |----> 0
          +--------+     +--------+     +--------+

The trivial cases return a list with null next and previous pointers.
