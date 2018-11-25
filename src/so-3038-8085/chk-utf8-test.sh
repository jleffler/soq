#!/bin/sh
# SO 3038-8085

echo -n 'привет мир' > вход
rmk utf8-test
./utf8-test
grep -q 'привет мир' выход && echo OK

