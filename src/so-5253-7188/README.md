### Stack Overflow Question 5253-7188

[SO 5253-7188](https://stackoverflow.com/q/52537188) &mdash;
Format strings safely when vsnprintf is not available

There are comments after my answer from [Supercat](
https://stackoverflow.com/users/363751/supercat):

* Such code would not be appropriate in security-sensitive contexts,
  because a malevolent caller could pass a string whose content will be
  changed (and made longer) by code in another thread.
  I think the best way to handle such functions is to write a
  generalized vxprintf function which accepts a double-indirect pointer
  to a function which will passed that pointer and any data to be
  output.
  The caller of the generalized function could create a struct whose
  first member was a pointer to the callback, and which would use the
  rest of the structure as needed.
  Such a function could then be used as the "core" for all other kinds
  of printf defined by the Standard, as well as many useful types that
  aren't (e.g. a 'graphics printf' to render text on a graphics screen).
  I suspect many implementations actually chain all their printf
  functions to a common routine, but the exact means of doing so vary.

I tend towards the view that this is a non-problem.
It depends on the context in which you're working, I suppose.
If you're trying to write a general purpose library for use by others,
then maybe it might perhaps be almost relevant (but maybe you can tell
I'm not wholly convinced by that).
If you're dealing with a defective machine (because only defective
systems do not have vsnprintf() already installed), you probably aren't
dealing with other people's potentially hostile threaded code which
requires enormous slight of hand to achieve the hypothesized
malfeasance.

A phrase involving 'mountains' and 'molehills' springs to mind.
It was tempting to mark the commentary "no longer needed", but I can
always use this as a way of snarking back at the modestly pointless
remarks.
