# Miscellaneous directory

Initially, to hold `soq-head.mk` and` soq-tail.mk`, the common makefile
fragments.

Also `l1-makefile`, a template for a makefile in a level-1 subdirectory
(_`so-xxxx-yyyy`_) under the `soq` top-level directory.
These are usually transients — they are either removed or moved to the
`soq/src` directory.

In the `src` directory, there is a script to create makefiles
(`mkmk.sh`), as well as 'updmkfile.sh` to update the `makefile` in the
`src` directory and `add-readme.sh` to create a skeletal `README.md`.

Other files if needed.
