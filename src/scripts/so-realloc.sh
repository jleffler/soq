#!/bin/sh
#
# Standard comment on misusing realloc

tr -s ' \t\n' '   ' <<'EOF'

Note that using `realloc()` like this `old_size = function_of(old_size);
old_ptr = realloc(old_ptr, old_size);` risks leaking the previous memory
allocation.
If `realloc()` fails, you've lost the pointer to the old memory (and the
size of the old block too), so you have a memory leak as well failing to
allocate more space.

Use code like: `size_t new_size = function_of(old_size); void *new_ptr =
realloc(old_ptr, new_size); if (new_ptr == NULL) { …handle failure…
} old_ptr = new_ptr; old_size = new_size;`.

This keeps control of the old space until you know the memory allocation
succeeded.

EOF
echo ''
