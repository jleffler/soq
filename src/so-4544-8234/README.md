SO 4544-8234

Not so much interesting for the program — I added average to make it
slightly more interesting — but as an opportunity to mess with
generating temperature data for each month of a year.

The program needs a series of lines, each with:

* year
* month
* 28-31 days of temperatures
* Fields are space separated
* Temperatures will be to hundredths of a degree (2 dp)

The code will determine the minimum, maximum and average for each month.

Unstated: the temperatures will be either highs or lows, but all the same category.

Generating the data:

* Pretend we have a 365-day (366 for leap years) sinusoidal wave form for the base data.
* Minimum temperature
* Maximum temperature
* Date of coldest temperature

Apply Gaussian perturbation to the values (average 0, standard deviation 5, say).
Assume temperatures are in ºC.

Example:

* Minimum: -4.
* Maximum: 28.
* Coldest day: Feb 4th (day 35).

Output format should be by month.

* The `perturb` command can deal with the perturbations.
* Can use Awk or Perl to generate the sinusoid.
* Need to study how to get lopsided data distributions rather than pure sinusoid.
* Maybe two sinusoids combined, with different amplitudes and different phases:
  * A sin (D * x) + B sin (D * x + y)

Monthly grouping presents its own little set of issues.

