#!/bin/bash
for i in {01..50}
do
  echo "stdout $i"
  echo "stderr $i" >&2
done
