#!/bin/sh
# SO 3038-8085

echo 'привет мир' > вход
make wchar-test
./wchar-test
grep -q 'привет мир' выход && echo OK

