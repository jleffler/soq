#!/bin/sh


#     ╔═════════════════╦═════════╦═════════╗
#     ║ Version         ║ Time 1  ║ Time 2  ║
#     ╠═════════════════╬═════════╬═════════╣
#     ║ Lucas A Shell   ║ 440.945 ║ 459.713 ║
#     ║ Awk 256         ║  45.194 ║  41.753 ║
#     ║ Chepner 1 Shell ║  42.515 ║  46.086 ║
#     ║ Chepner 2 Shell ║  17.598 ║  19.177 ║
#     ║ Leffler Shell   ║  16.028 ║  25.833 ║
#     ║ Python 7000     ║   7.211 ║   8.024 ║
#     ║ Awk 7000        ║   6.925 ║   5.977 ║
#     ║ Perl 7000       ║   1.337 ║   1.390 ║
#     ╚═════════════════╩═════════╩═════════╝

# 233707
#
# 2017-11-24 23:37:50.660  -  41.753s  -  sh awkscript.sh file
# 2017-11-24 23:37:58.169  -  5.977s  -  sh awkscript.sh file
# 2017-11-24 23:38:45.664  -  46.086s  -  bash chepner-1.sh file
# 2017-11-24 23:39:06.950  -  19.177s  -  bash chepner-2.sh file
# 2017-11-24 23:39:33.914  -  25.833s  -  sh jlscript.sh file
# 2017-11-24 23:47:16.394  -  459.713s  -  sh opscript.sh file
# 2017-11-24 23:47:19.489  -  1.390s  -  perl jlscript.pl file
# 2017-11-24 23:47:28.769  -  8.024s  -  python3 pyscript.py file

# Shell variables (unused in this script)
# t_tee='╦'
# b_tee='╩'
# l_tee='╠'
# r_tee='╣'
# blc='╚'
# tlc='╔'
# brc='╝'
# trc='╗'
# x_mid='╬'
# x_bar='═'
# x_pip='║'

sh tab-normal.sh <<'End-Input-Data-1' | awk -f tabulate.awk

    Script
    Samples
    Mean
    Std Dev
    Min
    Max

    Lucas A Shell
    7
    440.945
    23.23
    409.213
    490.319

    Awk 256
    7
    45.194
    3.123
    40.100
    49.234

End-Input-Data-1


sh tab-normal.sh <<'End-Input-Data-2' | awk -f tabulate.awk

    Version         
    Time 1  
    Time 2 

    Lucas A Shell   
    440.945 
    459.713 

    Awk 256         
    45.194 
    41.753 

    Chepner 1 Shell 
    42.515 
    46.086 

    Chepner 2 Shell 
    17.598 
    19.177 

    Leffler Shell   
    16.028 
    25.833 

    Python 7000     
    7.211 
    8.024 

    Awk 7000        
    6.925 
    5.977 

    Perl 7000       
    1.337 
    1.390 

End-Input-Data-2
