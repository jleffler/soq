### Stack Overflow Question 0253-0751

[SO 0253-0751](http://stackoverflow.com/q/02530751) &mdash;
How can I partial compare two strings in C?

This ends up as a speed comparison exercise for Boyer-Moore (BM) versus
Knuth-Morris-Pratt (KMP) search algorithms.
It turns out the KMP algorithm isn't very fast, at least not for the texts
being searched here.

The KMP and BM searches are adaptations of code lifted from:

    Christian Charras - Thierry Lecroq
    Laboratoire d'Informatique de Rouen
    Université de Rouen
    Faculté des Sciences et des Techniques
    76821 Mont-Saint-Aignan Cedex
    FRANCE
    e-mails: {Christian.Charras, Thierry.Lecroq}@laposte.net

* http://www-igm.univ-mlv.fr/~lecroq/string/node14.html   BM
* http://www-igm.univ-mlv.fr/~lecroq/string/node8.html    KMP

The original code embedded a fixed call-back (`OUTPUT(j)`) into the
search.
The revised code doesn't assume anything about the callback, but rather
returns the information in a form that allows the calling code to decide
what to do.
It is an open question how well the revised code performs, but it is at
least flexible.

The tests use a version of the King James Bible as the large text to
search.
The bible.words file lists distinct words and a count of the appearances
of that word.
It is case-sensitive, and includes apostrophes as a 'letter'.


