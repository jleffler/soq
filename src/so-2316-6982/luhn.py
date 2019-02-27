#!usr/bin/python
"""Luhn Algorithm over 1000 Amex Trial Numbers - SO 2316-6982."""

min_base = 37828224631000
max_base = 37828224631999

def luhn(number):
    """luhn(): Add Luhn check-digit to end of number."""
    def sum_digits(n):
        return sum([int(d) for d in str(n)])
    n = number * 10
    w = 1
    x = 0
    for digit in str(n)[::-1]:
        x += sum_digits(w * int(digit))
        w = 3 - w
    y = (x % 10)
    if y != 0:
        y = 10 - y
    return n + y

# Borrowed from Wikipedia via SO 2017-9439
def luhn_checksum(card_number):
    def digits_of(n):
        return [int(d) for d in str(n)]
    digits = digits_of(card_number)
    odd_digits = digits[-1::-2]
    even_digits = digits[-2::-2]
    checksum = 0
    checksum += sum(odd_digits)
    for d in even_digits:
        checksum += sum(digits_of(d*2))
    return checksum % 10

def is_luhn_valid(card_number):
    return luhn_checksum(card_number) == 0

# External checks
for ccn in [4532015112830366, 6011514433546201, 6771549495586802, 6771549495586803,
            79927398713, 378282246310005, 378282246310013, 378282246310021]:
    result = is_luhn_valid(ccn)
    print format(ccn, '>16'), ' Correct:' + str(result)

# Generate CCNs
for i in range(min_base, max_base+1):
    ccn = luhn(i)
    result = is_luhn_valid(ccn)
    print format(ccn, '>16'), ' Correct:' + str(result)
