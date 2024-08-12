### Stack Overflow Question 5495-1700

[SO 5495-1700](https://stackoverflow.com/q/54951700) &mdash;
Freed BST but still getting memory leak C

[SO 7400-0791](https://stackoverflow.com/q/74000791) &mdash;
Count the leaves in a given Binary Tree

Neither question provided an MCVE.

* `bst31.c` - code trying to stimulate a leak but failing. 

* `bst41.c` - code counting leaf nodes.

  The code in the question used a static variable in its `Leaves()`
  function, a major no-no for a recursive function.

