### Stack Overflow Question 3945-8053

[SO 3945-8053](https://stackoverflow.com/q/39458053) &mdash;
Determine shift for simple substitution cipher in C

## Answer

The basic idea suggested by
[tofro](https://stackoverflow.com/users/5785362/tofro) in their
[comment](https://stackoverflow.com/questions/39458053/determine-shift-for-simple-substitution-cipher-in-c#comment66237865_39458053)
is sound.

The [Chi-Squared Test](https://en.wikipedia.org/wiki/Chi-squared_test)
computes the sum of the squares of the differences between the expected
value, _E<sub>i</sub>_, and the observed value, _O<sub>i</sub>_, divided
by the expected value.  The Wikipedia page even mentions an application:

> In cryptanalysis, chi-square test is used to compare the distribution
> of plaintext and (possibly) decrypted ciphertext.  The lowest value of
> the test means that the decryption was successful with high
> probability.

Applying that to the problem on hand, you've provided a table of the
expected frequencies of different letters in ordinary English text.  We
need a program to apply the Caesar Cipher to a given plaintext (or
ciphertext):

### `ec97.c`

    …file ec97.c…

Example use (program `ec97`):

    $ ec97 3 <<< 'The quick brown fox jumped over the lazy dog!'
    Wkh txlfn eurzq ira mxpshg ryhu wkh odcb grj!
    $ ec97 23 <<< 'Wkh txlfn eurzq ira mxpshg ryhu wkh odcb grj!'
    The quick brown fox jumped over the lazy dog!
    $

And we need a program which:

1. Counts the frequencies of the letters in the input, F<sub>l</sub>,
   ignoring case, plus the total number of letters, N, in the input.
2. For each possible key, computes the Χ² value using the
   F<sub>i</sub> value as the _O<sub>i</sub>_ and the letter frequency,
   L<sub>i</sub>×N as _E<sub>i</sub>_, with some careful dinking with
   the subscripts.
3. Find the smallest Χ² value; it is almost certainly the correct encryption key.

Or, in code:

### `dc97.c`

    …file dc97.c…

### Testing

Example run:

    $ ec97 3 <<< 'The quick brown fox jumped over the lazy dog!' | dc97
    'A' =    143.784398
    'B' =    564.772479
    'C' =    125.131609
    'D' =     87.069134
    'E' =    178.249272
    'F' =     90.994048
    'G' =    194.326935
    'H' =    301.117365
    'I' =    710.786241
    'J' =    147.377473
    'K' =    304.179348
    'L' =    243.699823
    'M' =    137.639230
    'N' =    183.885553
    'O' =    135.720804
    'P' =    106.261239
    'Q' =    196.046792
    'R' =    506.812184
    'S' =    517.893291
    'T' =    106.267925
    'U' =    375.525078
    'V' =    202.806561
    'W' =    116.660543
    'X' =    304.590809
    'Y' =    364.746822
    'Z' =    139.113568
    Best match is (3) 'D' =  87.069134
    $

I also ran it on the program source code, and the makefile in the
directory, and a couple of data files.  The first is a piece of nonsense
often called ['The Great
Panjandrum'](https://en.wikisource.org/wiki/The_Grand_Panjandrum):

    So she went into the garden
    to cut a cabbage-leaf
    to make an apple-pie
    and at the same time
    a great she-bear coming down the street
    pops its head into the shop
    What no soap
    So he died
    and she very imprudently married the Barber
    and there were present
    the Picninnies
    and the Joblillies
    and the Garyulies
    and the great Panjandrum himself
    with the little round button at top
    and they all fell to playing the game of catch-as-catch-can
    till the gunpowder ran out at the heels of their boots

and the second is crafted carefully for this question:

    Bond was on a roll, playing jazz on his sax.
    In all of his doings, nothing was as bad as what was going on now,
    but nary a jocular hint did his writing contain that
    all was not going as his boss though it would.
    Quit? Zounds!  No way to quit now.

There are no e's in that, which, it might be thought, could throw things
off, but there isn't a problem, it seems.

    $ x=$(random 1 25)
    $ ec97 $x < great.panjandrum
    Uq ujg ygpv kpvq vjg ictfgp
    vq ewv c ecddcig-ngch
    vq ocmg cp crrng-rkg
    cpf cv vjg ucog vkog
    c itgcv ujg-dgct eqokpi fqyp vjg uvtggv
    rqru kvu jgcf kpvq vjg ujqr
    Yjcv pq uqcr
    Uq jg fkgf
    cpf ujg xgta kortwfgpvna octtkgf vjg Dctdgt
    cpf vjgtg ygtg rtgugpv
    vjg Rkepkppkgu
    cpf vjg Lqdnknnkgu
    cpf vjg Ictawnkgu
    cpf vjg itgcv Rcplcpftwo jkougnh
    ykvj vjg nkvvng tqwpf dwvvqp cv vqr
    cpf vjga cnn hgnn vq rncakpi vjg icog qh ecvej-cu-ecvej-ecp
    vknn vjg iwprqyfgt tcp qwv cv vjg jggnu qh vjgkt dqqvu
    $ ec97 $x | dc97
    'A' =   3403.710518
    'B' =   1821.123417
    'C' =     29.719952
    'D' =   5238.969620
    'E' =   2077.413735
    'F' =   8274.966485
    'G' =   2446.331525
    'H' =   8950.309208
    'I' =   1362.257963
    'J' =   4419.368172
    'K' =   3161.502276
    'L' =   3113.030682
    'M' =   7778.647756
    'N' =   1112.302912
    'O' =   1497.782346
    'P' =   1490.896824
    'Q' =  10395.032795
    'R' =   1985.696886
    'S' =   2382.319358
    'T' =   4874.708427
    'U' =   3280.570608
    'V' =   1467.488275
    'W' =   7318.221432
    'X' =   5634.124795
    'Y' =   3108.392584
    'Z' =   2849.154134
    Best match is (2) 'C' =  29.719952
    $ echo "Key = $x"
    Key = 2
    $

    $ x=$(random 1 25)
    $ ec97 $x < bond.jazz
    Ylka txp lk x olii, mixvfkd gxww lk efp pxu.
    Fk xii lc efp alfkdp, klqefkd txp xp yxa xp texq txp dlfkd lk klt,
    yrq kxov x glzrixo efkq afa efp tofqfkd zlkqxfk qexq
    xii txp klq dlfkd xp efp ylpp qelrde fq tlria.
    Nrfq? Wlrkap!  Kl txv ql nrfq klt.
    $ ec97 $x < bond.jazz | dc97
    'A' =   2630.974532
    'B' =   2107.704681
    'C' =   1473.828862
    'D' =    865.368278
    'E' =    715.940980
    'F' =   1010.885486
    'G' =   2881.481606
    'H' =   3297.014998
    'I' =   1302.909485
    'J' =    871.665974
    'K' =    917.232399
    'L' =   2716.342024
    'M' =   2525.973294
    'N' =   2077.065275
    'O' =   3096.667665
    'P' =   2211.782909
    'Q' =   1793.302623
    'R' =   1427.340376
    'S' =   1537.934006
    'T' =    702.667000
    'U' =   3489.590647
    'V' =   3111.999371
    'W' =   1445.825861
    'X' =    142.412135
    'Y' =   2671.998367
    'Z' =   1977.131986
    Best match is (23) 'X' = 142.412135
    $ echo "Key = $x"
    Key = 23
    $

It seems to work pretty well.
