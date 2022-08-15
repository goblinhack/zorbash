#!/bin/sh
for i in *.hpp *.cpp
do
  echo $i
  clang-format -i $i
done
