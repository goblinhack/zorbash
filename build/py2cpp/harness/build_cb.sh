#!/bin/bash
set -e
H=/tmp/harness2; rm -f $H/b_*.o $H/b_*.cpp $H/batch_* $H/runner
cd /home/claude/src
find things modules -name '*.cpp' | sort > $H/files.txt
split -l 60 -d -a 3 $H/files.txt $H/batch_
for b in $H/batch_*; do
  n=$(basename $b)
  { echo '#include "my_native.hpp"'; while read f; do echo "#include \"$f\""; done < $b; } > $H/b_$n.cpp
done
for f in $H/b_batch_*.cpp; do g++ -std=c++2a -O0 -w -I$H -I/home/claude/src -c $f -o $f.o 2>&1 | head -20; done
cp /home/claude/src/native_modules.cpp $H/b_nm.cpp
g++ -std=c++2a -O0 -w -I$H -I/home/claude/src -c $H/b_nm.cpp -o $H/b_nm.o 2>&1 | head
g++ -std=c++2a -O0 -w -I$H -c $H/main.cpp -o $H/main.o 2>&1 | head
g++ -o $H/runner $H/main.o $H/b_nm.o $H/b_batch_*.o
$H/runner > $H/cpp.log
wc -l $H/cpp.log
