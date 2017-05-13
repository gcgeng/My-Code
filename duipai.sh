#!/bin/bash
while true; do
  ./r > input
  ./a.out < input > output.a
  ./check < output.a > output.b
  diff output.a input
  if [ $? -ne 0 ] ; then break; fi
done
