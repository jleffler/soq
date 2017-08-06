# Create and Include Header Files

In modern C, header files are crucial tools that must be designed and used correctly.  They allow the compiler to cross-check independently compiled parts of a program.

Headers declare types, functions, macros etc that are needed by the consumers of a set of facilities.
All the code that uses any of those facilities includes the header.
All the code that defines those facilities includes the header.
This allows the compiler to check that the uses and definitions match.

