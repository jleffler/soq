random -C -c -e -T '%W%5:15w %W%6:20w %[1000:9999]d %{%Y-%m-%d %H:%M:%S}[1400000000:1600000000]L %W%10:29w' |
dribbler -i /dev/stdin -s 2 -r 0.6 -t |
tstamp -f 3
