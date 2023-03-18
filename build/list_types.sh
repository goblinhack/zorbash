#!/bin/bash

PRE=$(mktemp) || exit 1
PAYLOAD=$(mktemp) || exit 1
POST=$(mktemp) || exit 1
OUT=$(mktemp) || exit 1
TMP=$(mktemp) || exit 1
IN=README.md

for i in amulets armor boots buffs cloaks debuffs doors food gauntlets items keys mobs monsters player potions rings shield skills staffs treasure weapons traps
do
  num_of_this_type=$(ls python/things/$i/*.py | grep -v swing | grep -v carry | grep -v radial | grep -v laser | grep -v effect | grep -v projectile | wc -l)
  echo "- $num_of_this_type x $i" >> $PAYLOAD
done

sort -r -n +1 $PAYLOAD > $TMP
mv $TMP $PAYLOAD

sed "1,/begin type marker/!d" $IN > $PRE
sed "/end type marker/,\$!d" $IN | tail -n +1 - > $POST

cat $PRE $PAYLOAD $POST > $OUT
diff $IN $OUT

if [ "$1" = "do" ]; then
  mv $OUT $IN
fi
