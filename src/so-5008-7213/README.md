### Stack Overflow Question 5008-7213

[SO 5008-7213](https://stackoverflow.com/q/50087213) &mdash;
execvp() prints invalid option -- &#39;

A Lex (Flex) and Yacc (Bison) problem.

Flex, it appears, returns `yytext` as a pointer into a longer string,
which is null terminated at the end of the token when it returns, but
the null gets overwritten with the original input when `yylex()`.

The 'fixed' code uses `strdup()` to make copies of the token in
`insertArg()`, which resolves the problem.
One question that is as yet unanswered is whether doing that in the
grammar actions does the job quick enough.

The code in `main()` is written with a loop, but the loop would only
occur if you failed to execute the command — and that generates a
'syntax error' becaause an empty input is not valid according to the
syntax.
Despite the loop, therefore, it is a one-shot program.
