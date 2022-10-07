#!/bin/bash
cd src
for i in *.cpp *.hpp
do
  case $i in
    *stb*)
      ;;
    *lzo*)
      ;;
    *ramdisk*)
      ;;
    *)
      echo Checking $i...
      clang-tidy -checks=clang-analyzer,-clang-analyzer-cplusplus  $i -- -I/usr/include/SDL2 -I/usr/include/python3.10 -include config.h -O3  -Wall  -std=c++2a    -MMD -MP -c
    ;;
  esac
done
