# SO 18390259 - Organizing inconsistent values

trap 'rm -f data; exit 1' 0 1 2 3 13 15

# Input data:
cat >data <<'EOF'
bm_wp_upg_o_t1micro, sight, value = 3, zoom = 3, recoil = 1, spread_moving = -1 
bm_wp_upg_o_marksmansight_rear, sight, value = 3, zoom = 1, recoil = 1, spread = 1 
bm_wp_upg_o_marksmansight_front, extra, value = 1 
bm_wp_m4_upper_reciever_edge, upper_reciever, value = 3, recoil = 1 
bm_wp_m4_upper_reciever_round, upper_reciever, value = 1 
bm_wp_m4_uupg_b_long, barrel, value = 4, damage = 1, spread = 1, spread_moving = -2, concealment = -2
EOF

# Output data:
#                              id,          type,value,zoom,recoil,spread_moving,spread,damage,concealment
#             bm_wp_upg_o_t1micro,         sight,    3,   3,     1,           -1,      ,      ,           
#  bm_wp_upg_o_marksmansight_rear,         sight,    3,   1,     1,             ,     1,      ,           
# bm_wp_upg_o_marksmansight_front,         extra,    1,    ,      ,             ,      ,      ,           
#    bm_wp_m4_upper_receiver_edge,upper_receiver,    3,    ,     1,             ,      ,      ,           
#   bm_wp_m4_upper_receiver_round,upper_receiver,    1,    ,      ,             ,      ,      ,           
#            bm_wp_m4_uupg_b_long,        barrel,    4,    ,      ,           -2,     1,     1,         -2

# The awk script adapts to what it finds in the data.  The first two
# columns (id and type) are fixed; the others are generated as needed.

awk 'BEGIN  {
                # f_idx[field] holds the column number c for a field=value item
                # f_name[c]    holds the names
                # f_width[c]   holds the width of the widest value (or the field name)
                # f_fmt[c]     holds the appropriate format
                FS = " *, *"; n = 2;
                f_name[0] = "id";   f_width[0] = length(f_name[0])
                f_name[1] = "type"; f_width[1] = length(f_name[1])
            }
            {
                #-#print NR ":" $0
                line[NR,0] = $1
                len = length($1)
                if (len > f_width[0])
                    f_width[0] = len
                line[NR,1] = $2
                len = length($2)
                if (len > f_width[1])
                    f_width[1] = len
                for (i = 3; i <= NF; i++)
                {
                    split($i, fv, " = ")
                    #-#print "1:" fv[1] ", 2:" fv[2]
                    if (!(fv[1] in f_idx))
                    {
                        f_idx[fv[1]] = n
                        f_width[n++] = length(fv[1])
                    }
                    c = f_idx[fv[1]]
                    f_name[c] = fv[1]
                    gsub(/ /, "", fv[2])
                    len = length(fv[2])
                    if (len > f_width[c])
                        f_width[c] = len
                    line[NR,c] = fv[2]
                    #-#print c ":" f_name[c] ":" f_width[c] ":" line[NR,c]
                }
            }
     END    {
                for (i = 0; i < n; i++)
                    f_fmt[i] = "%s%" f_width[i] "s"
                #-#for (i = 0; i < n; i++)
                #-#    printf "%d: (%d) %s %s\n", i, f_width[i], f_name[i], f_fmt[i]
                #-#    pad = ""
                for (j = 0; j < n; j++)
                {
                    printf f_fmt[j], pad, f_name[j]
                    pad = ","
                }
                printf "\n"
                for (i = 1; i <= NR; i++)
                {
                    pad = ""
                    for (j = 0; j < n; j++)
                    {
                        printf f_fmt[j], pad, line[i,j]
                        pad = ","
                    }
                    printf "\n"
                }
            }' data

rm -f data
trap 0
