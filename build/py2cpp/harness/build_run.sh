#!/bin/bash
set -e
H=/tmp/harness; rm -f $H/b_*.o $H/b_*.cpp $H/batch_*
cd /home/claude/src
find things modules -name '*.cpp' | sort > $H/files.txt
split -l 60 -d -a 3 $H/files.txt $H/batch_
for b in $H/batch_*; do
  n=$(basename $b)
  { echo '#include "my_native.hpp"'; while read f; do echo "#include \"$f\""; done < $b; } > $H/b_$n.cpp
done
ls $H/b_batch_*.cpp | xargs -P1 -I{} sh -c 'g++ -std=c++2a -O0 -w -I'$H' -I/home/claude/src -c {} -o {}.o 2>&1 | head -20'
g++ -std=c++2a -O0 -w -I$H -c $H/main.cpp -o $H/main.o
g++ -o $H/runner $H/main.o $H/b_batch_*.o
$H/runner > $H/cpp.log
wc -l $H/cpp.log
