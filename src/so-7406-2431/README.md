## Stack Overflow Question 7406-2431

[SO 7406-2431](https://stackoverflow.com/q/74062431) &mdash;
Directories being found but not being recognized as directories

### Code

* `dirlist17.c` — MCVE code from question
  * Modified enough to compile cleanly - extra headers, missing unused variables

* `dirlist43.c` — Adequately working code
  * Compile with `-DUNIX` for POSIX systems that use forward slash for the directory separator.
  * Otherwise, it uses backslashes as the directory separator
  * Compile with `-DDEBUG` to get copious output.

* `dirlist67.c` — Interim solution 2
* `dirlist73.c` — Interim solution 1

### Sample output

Output from `dirlist43` compiled for Unix without -DDEBUG:

```
FOLDERMAIN: /Users/jonathanleffler/soq/src/so-7406-2431
FILE: /Users/jonathanleffler/soq/src/so-7406-2431/dirlist17
FILE: /Users/jonathanleffler/soq/src/so-7406-2431/dirlist43
FILE: /Users/jonathanleffler/soq/src/so-7406-2431/dirlist73
CHECK: 1
FOLDER: /Users/jonathanleffler/soq/src/so-7406-2431/dirlist43.dSYM
CHECK: 2
FOLDER: /Users/jonathanleffler/soq/src/so-7406-2431/dirlist43.dSYM/Contents
CHECK: 3
FOLDER: /Users/jonathanleffler/soq/src/so-7406-2431/dirlist43.dSYM/Contents/Resources
CHECK: 4
FOLDER: /Users/jonathanleffler/soq/src/so-7406-2431/dirlist43.dSYM/Contents/Resources/DWARF
FILE: /Users/jonathanleffler/soq/src/so-7406-2431/dirlist43.dSYM/Contents/Resources/DWARF/dirlist43
FILE: /Users/jonathanleffler/soq/src/so-7406-2431/dirlist43.dSYM/Contents/Info.plist
FILE: /Users/jonathanleffler/soq/src/so-7406-2431/makefile
FILE: /Users/jonathanleffler/soq/src/so-7406-2431/dirlist67.c
FILE: /Users/jonathanleffler/soq/src/so-7406-2431/dirlist67
FILE: /Users/jonathanleffler/soq/src/so-7406-2431/dirlist73.c
CHECK: 5
FOLDER: /Users/jonathanleffler/soq/src/so-7406-2431/dirlist73.dSYM
CHECK: 6
FOLDER: /Users/jonathanleffler/soq/src/so-7406-2431/dirlist73.dSYM/Contents
CHECK: 7
FOLDER: /Users/jonathanleffler/soq/src/so-7406-2431/dirlist73.dSYM/Contents/Resources
CHECK: 8
FOLDER: /Users/jonathanleffler/soq/src/so-7406-2431/dirlist73.dSYM/Contents/Resources/DWARF
FILE: /Users/jonathanleffler/soq/src/so-7406-2431/dirlist73.dSYM/Contents/Resources/DWARF/dirlist73
FILE: /Users/jonathanleffler/soq/src/so-7406-2431/dirlist73.dSYM/Contents/Info.plist
FILE: /Users/jonathanleffler/soq/src/so-7406-2431/README.md
FILE: /Users/jonathanleffler/soq/src/so-7406-2431/dirlist43.c
FILE: /Users/jonathanleffler/soq/src/so-7406-2431/.gitignore
CHECK: 9
FOLDER: /Users/jonathanleffler/soq/src/so-7406-2431/dirlist67.dSYM
CHECK: 10
FOLDER: /Users/jonathanleffler/soq/src/so-7406-2431/dirlist67.dSYM/Contents
CHECK: 11
FOLDER: /Users/jonathanleffler/soq/src/so-7406-2431/dirlist67.dSYM/Contents/Resources
CHECK: 12
FOLDER: /Users/jonathanleffler/soq/src/so-7406-2431/dirlist67.dSYM/Contents/Resources/DWARF
FILE: /Users/jonathanleffler/soq/src/so-7406-2431/dirlist67.dSYM/Contents/Resources/DWARF/dirlist67
FILE: /Users/jonathanleffler/soq/src/so-7406-2431/dirlist67.dSYM/Contents/Info.plist
FILE: /Users/jonathanleffler/soq/src/so-7406-2431/dirlist17.c
CHECK: 13
FOLDER: /Users/jonathanleffler/soq/src/so-7406-2431/dirlist17.dSYM
CHECK: 14
FOLDER: /Users/jonathanleffler/soq/src/so-7406-2431/dirlist17.dSYM/Contents
CHECK: 15
FOLDER: /Users/jonathanleffler/soq/src/so-7406-2431/dirlist17.dSYM/Contents/Resources
CHECK: 16
FOLDER: /Users/jonathanleffler/soq/src/so-7406-2431/dirlist17.dSYM/Contents/Resources/DWARF
FILE: /Users/jonathanleffler/soq/src/so-7406-2431/dirlist17.dSYM/Contents/Resources/DWARF/dirlist17
FILE: /Users/jonathanleffler/soq/src/so-7406-2431/dirlist17.dSYM/Contents/Info.plist
```
