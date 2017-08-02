#!/bin/sh
#
# Generate a sinusoidal wave over Y days, min N, max X, low at L

awk '
BEGIN {
    N = -4
    X = 28
    Y = 365
    L = 35
    r = (X - N) / 2
    m = (X + N) / 2
    pi = atan2(1, 1) * 4
    dr = 180 / pi
    dd = 2 * pi / Y             # Daily delta in radians
    start = -pi / 2 - L * dd
    end = 3 * pi / 2 - L * dd
    for (i = 0; i < Y; i++)
    {
        a = start + i * dd      # Angle in radians
        b = a * dr              # Angle in degrees
        s = sin(a)
        v = r * s + m
        printf "%3d: %12.6f = %12.6f => %9.6f = %12.6f\n", i, a, b, s, v
    }
}'

