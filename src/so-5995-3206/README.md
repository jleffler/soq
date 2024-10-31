### Stack Overflow Question 5995-3206

[SO 5995-3206](https://stackoverflow.com/q/59953206) &mdash;
Linked lists recursive function which deletes odd values from the list.

### Answer

The key is defining what `listDeleteOdd()` does.  It returns a pointer to
a list of nodes which is either empty or contains only even values — a
'clean list'.

Internally, it does that in three different operations:

1. The input list is empty (NULL); return NULL (base case).
2. The first node in the list is odd; capture the next node, delete the
   current node; recurse to return the clean list starting at the next
   node.
3. By elimination, the first node in the list is even.  Capture the list
   of even values starting at the next node (recurse).  Make the current
   node's next pointer (`link`) point to the clean list, and return the
   current node as the start of the (now clean) list.

