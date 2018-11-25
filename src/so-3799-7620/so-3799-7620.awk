#!/opt/gnu/bin/awk -f
#
# SO 3799-7620


NR == 1 { print; hdr1 = $1; hdr2 = $2; next }
        {
            line++;
            #print line ": [", $0, "]"
            col1[line] = $1
            col2[line] = $2
            for (field = 3; field <= NF; field++)
            {
                if ($field == "0") continue
                n = split($field, a, ",")
                for (sf = 1; sf <= n; sf++)
                {
                    val = a[sf]
                    x = field SUBSEP val
                    if (x in sf_idx)
                        idx = sf_idx[x]
                    else
                    {
                        idx = ++sf_cnt[field]
                        sf_idx[field, val] = idx
                        sf_val[field, idx] = val
                    }
                    cols[line,field,idx] = 1
                    #printf "cols[%d][%d][%d] = %s\n", line, field, idx, cols[line, field, idx]
                }
            }
            if (max_nf < NF)
                max_nf = NF
        }
END     {
            max_line = line
            #print "Lines:", max_line, "; fields:", max_nf
            # Line 2 heading
            printf "#%s   %s", hdr1, hdr2
            for (field = 3; field <= max_nf; field++)
            {
                for (sf = 1; sf <= sf_cnt[field]; sf++)
                    printf "   %s", sf_val[field, sf]
            }
            print ""
            # Data lines
            for (line = 1; line <= max_line; line++)
            {
                printf "%s   %s", col1[line], col2[line]
                for (field = 3; field <= max_nf; field++)
                {
                    #print "field:", field, "sub-fields:", sf_cnt[field]
                    for (sf = 1; sf <= sf_cnt[field]; sf++)
                    {
                        #print "line:", line, "; field:", field, "; sf:", sf
                        x = line SUBSEP field SUBSEP sf
                        if (x in cols)
                            val = sf_val[field, sf]
                        else
                            val = "0"
                        printf "   %s", val
                    }
                }
                print ""
            }
        }
