NR == FNR { lines1[FNR] = $0; rows1[$0] = FNR; num1 = FNR }
NR != FNR { lines2[FNR] = $0; rows2[$0] = FNR; num2 = FNR }
END {
    # Lines in common or in file 1 only
    for (i = 1; i <= num1; i++)
    {
        if (rows2[lines1[i]] > 0)
            print "file.3: " lines1[i]
        else
            print "file.1: " lines1[i]
    }
    # Lines only in file 2
    for (i = 1; i <= num2; i++)
    {
        if (rows1[lines2[i]] == 0)
            print "file.2: " lines2[i]
    }
}
