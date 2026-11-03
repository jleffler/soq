Demonstrate Apple-specific 4-argument main()
============================================

Apple compilers support a 4-argument version of `main()`:
```
int main(int argc, char **argv, char **envp, char **appv)
{
    …
}
```
One run of this command produced more or less this output.
Some environment variables are omitted, and others are truncated.
```
$ ./ala arg1 arg2
argc = 3
argv[0] = [[./ala]]
argv[1] = [[arg1]]
argv[2] = [[arg2]]
envp[0] = [[MANPATH=…]]
…
envp[7] = [[SHELL=/bin/bash]]
…
envp[18] = [[CDPATH=…]]
…
envp[20] = [[USER=jleffler]]
…
envp[28] = [[PATH=…]]
…
envp[39] = [[HOME=/Users/jleffler]]
…
envp[43] = [[DYLD_LIBRARY_PATH=…]]
…
envp[54] = [[_=./ala]]
appv[0] = [[executable_path=./ala]]
appv[1] = [[]]
appv[2] = [[]]
appv[3] = [[]]
appv[4] = [[ptr_munge=]]
appv[5] = [[main_stack=]]
appv[6] = [[executable_file=0x1a0100000d,0xa3d551b]]
appv[7] = [[dyld_file=0x1a0100000d,0xfffffff000b33ce]]
appv[8] = [[executable_cdhash=356070a258197a8a57377fed3ec6f31a1108fd7b]]
appv[9] = [[executable_boothash=20989a42a071826dd77f4014cc17e27a1e1db3c0]]
appv[10] = [[th_port=]]
appv[11] = [[security_config=0x0]]
$
```
