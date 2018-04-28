# Miscellaneous data files

Various data files collected from various sources at various times.

### Names

The web site https://names.mongabay.com/ provides lists of names in HTML derived from US Census data.

* [1000 most common US surnames](https://names.mongabay.com/most_common_surnames.htm)
* [300 most common US male first names](https://names.mongabay.com/male_names.htm)
* [1000 most common US female first names](https://names.mongabay.com/female_names.htm)
* [Zip Codes by US State — AL](https://data.mongabay.com/igapo/zip_codes/AL.htm)

There are lists for 301-600, 601-900, 901+ first names, and for 1001-2000, 2001-5000, etc surnames.

### Weighted frequencies

For the names, there are frequencies as a percentage.
To generate data for a random choice of name, use '`max_int(percentage *
100, 1)`' for the number of occurrences of a name.
Any name less with a frequency of less than 0.01% will appear once; more
frequent names will appear more often.

In the surnames, the most common name is SMITH with a frequency of 1.006
percent; it would appear 100 times in a list of names.
The 1000th name is VANG with a frequency of 0.012; it would appear once,
as would the 607th name, BEARD, with a frequency of 0.019.
Rounding up could be considered (so 0.015 would be rounded up to 2
appearances; 0.014 would round down to 1 appearance).
That would place the break between BERNARD (0.015, number 830) and
JOYNER (0.014, number 831).

In the male names data, JAMES (3.318, rank 1) and JOHN (3.271, rank 2)
would appear 332 and 327 times; WADE (0.045, rank 300) would appear 5
times.

In the female names data, MARY (2.629, rank 1) and PATRICIA (1.073, rank
2) would appear 263 and 107 times; CLAIRE (0.061, rank 300) would appear
6 times.
There are more variations and less concentration in the female names.

### Processing

For one-off exercises, reading a file each time for 1000 names is not
too onerous.
For repeated data generation, you begin to wonder if reading a file
each time is truly appropriate, or whether keeping the file in memory and
accessing it would be better.
It gets trickier with weighting.
The code could read the frequency and apply the selection algorithm the
appropriate number of times.
Maybe it depends on how many names there are in total.
