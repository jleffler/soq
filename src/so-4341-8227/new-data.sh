#!/bin/bash

n=${1:-50}
{
echo 1
random -n $n 0 1 | tr -d '\n'
echo
} > in-$n-$(date +%H%M%S)
