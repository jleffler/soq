### Stack Overflow Question 6529-2945

[SO 6529-2945](https://stackoverflow.com/q/65292945) &mdash;
Stack Overflow

> My goal is to write a simple generic linked list.

> I do not know how to create a perfect `listPrint` function because
> `printf` has to get the type of that value, plus I have to cast
> `ptr->data` to the appropiate format.  Currently I can print just `int`,
> using `printf("%i "`,*((int*)ptr->data))`.  How could I print any type of value
> like `int`,`float`,`char`...?

> When I pushBack to the list, I have to create an `int i` and then call
> `listPushBack(list, &i)`, but I would like to do this way
> `listPushBack(list,101)`.  I know that if I do the stuff like this I have
> to do this way, but what should I change in my code to allow me to
> `listPushBack(list,101)`.

> The elements stored in a given list will be the same type (list of
> `int`, list of `double`, list of `struct WhatEver *`, etc).

With outline code added.  This is my solution.

