#!/bin/sh
# SO 30388085

echo 'привет мир' > вход
make wchar-test
./wchar-test
grep -q 'привет мир' выход && echo OK

