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
      echo Formatting $i...
      clang-format -i $i
      git --no-pager diff $i
    ;;
  esac
done
