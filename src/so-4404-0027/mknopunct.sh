#!/bin/sh
#
# Create no-punctuation-linux.words from linux.words

source="linux.words"
target="no-punctuation-$source"

[ -f "$source" ] || { echo "$0: missing $source file" >&2; exit 1; }
[ -f "$target" ] && [ ! -w "$target" ] && { echo "$0: unwritable $target file" >&2; exit 1; }

exec grep '^[a-zA-Z]*$' "$source" > "$target"
