#!/bin/sh

grep -h -e '^[[:space:]]*#[[:space:]]*include[[:space:]]*<[^>]*>' -r "${@:-.}" |
sed 's/^[[:space:]]*#[[:space:]]*include[[:space:]]*<\([^>]*\)>.*/\1/' |
sort -u
