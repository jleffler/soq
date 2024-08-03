
https://stackoverflow.com/questions/10431305/how-to-reorder-items-in-a-table/10577425#10577425

How to reorder items in a table?




I have table (call it `my_table`) that can be simplified like this: `NAME`, `SEQ_NO`, `LOCKED`.

Items get removed and added and I want to reorder them (modify `SEQ_NO`)
in a way that the sequence always goes from `1` to `COUNT(*)` and items
that are locked retain their `SEQ_NO` and no unlocked item would get that
number.
Only unlocked items are updated with new `SEQ_NO`.

Example:

This:

    NAME  SEQ_NO    LOCKED
    Foo   1         N
    Bar   3         Y
    Abc   4         Y
    Baz   5         N
    Cde   7         N

would result in:

    NAME  SEQ_NO    LOCKED
    Foo   1         N
    Baz   2         N
    Bar   3         Y
    Abc   4         Y
    Cde   5         N

How could I do that?


JL answer: https://stackoverflow.com/a/10577425

Interesting for the CTE SQL - untested!
