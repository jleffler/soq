### Stack Overflow Question 3995-0926

[SO 3995-0926](https://stackoverflow.com/q/39950926) &mdash;
Quicksort implementation in C

2020-04-14 - Work In Progress

The code in `qs43.c` is my original answer, posted 2016-10-10,  It works on the sample
data.


However, on 2020-04-13,
[Nikola Petrovic](https://stackoverflow.com/users/2153491/nikola-petrovic)
[pointed out](https://stackoverflow.com/questions/39950926/quick-sort-implementation-in-c#comment108249954_39951640):

> Don't you need a terminating condition for the increment of left
> inside the nested while loop?
> If L={6,3,3}, your line `while (L[left] <= p_val) left++;` would
> continue to increment left and leave the higher bound of the array.

The code in the `qs43.c` does not sort a sub-array containing `{ 6, 3, 3
}`, as the code in `qs97.c` demonstrates.
I've not yet instrumented it enough to determine what the long-term fix
is.

I responded:

> @NikolaPetrovic — interesting question.
> One answer is "no", but the result isn't correct.
> I created an array of 9 elements, with the centre three being 6, 3, 3
> and the outer elements being clearly different.
> The code doesn't sort the centre three.
>
>     Bounds testing (sorting indexes 3..5):
>     UNSORTED DATA [0..8]: 999 998 997 6 3 3 -997 -998 -999
>     UNSORTED LIST [3..5]: 6 3 3 —
>     SORTED LIST [3..5]: 6 3 3
>     SORTED DATA [0..8]: 999 998 997 6 3 3 -997 -998 -999.
>
> It's not using the values out of the range; it isn't sorting the
> values in range.
> I'll investigate.

Nikola Petrovic is adamant about the necessary change:

> In your particular case it's not going outside the bounds because you
> added extra elements - i.e.
> your L is not {6,3,3}.
> If you were to use L = {6,3,3} it most certainly would go outside of
> the bounds.
> Whether it executes correctly would then only depend on the values in
> memory after L.
> Try changing that line to:
>
>     while(L[left] <= p_val && left < right)
>         left++;
>
> It should work then.

I re-responded:

> I used two versions of the test — the one shown and one with the
> signs on the 'out of bounds' numbers of opposite signs (changing `+`
> to `-` and `-` to `+`).
> Neither showed signs of using the out of bounds values.
> Nevertheless, the result is wrong, and I clearly need to do some
> surgery on the code.
> I will look at your suggestion; thanks.
> It will take me at least a few hours to get any update posted — I'm
> lucky enough to still have a thing called 'a job' and I need to pay
> some attention to that for a bit, and my dog needs a walk too, even
> though the temperature is a brisk -7ºC!
> Snow!

And Nikola countered:

> I don't see the relevance of personal matters in this.
> Debugging the code here proves my point https://pastebin.com/0AfGP8BA.
> It's your code (only the quicksort-related) and left clearly leaves
> the upper bound of L because there is nothing to prevent it from doing
> so.
> Changing the while to:
>
>     while (L[left] <= p_val && left < right)
>
> fixed it.
> Your code is written well regardless.

The change probably does fix the bug &mdash; but I've not verified it,
nor decided whether it is the solution I would choose.
At the time of typing, I've verified that there is a problem (data is
not sorted).

(The attack on my comment doesn't inspire me to deal with the issue in a
hurry.
It will be dealt with; it will take longer than originally projected, in
part because the attitude expressed by Nikola (not shown above) does not
induce warm feelings - it is an example of how not to win friends and
influence people the wway you want them influenced.)
