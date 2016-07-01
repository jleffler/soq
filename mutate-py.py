# SO 7365814 In-place array reordering
a = [8, 6, 7, 5, 3, 0, 9]
indices = [3, 6, 2, 4, 0, 1, 5]

for i in xrange(len(a)):
    x = a[i]
    j = i
    while True:
        k = indices[j]
        indices[j] = j
        if k == i:
            break
        a[j] = a[k]
        j = k
    a[j] = x

print a
