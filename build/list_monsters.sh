#!/bin/bash

PRE=$(mktemp) || exit 1
PAYLOAD=$(mktemp) || exit 1
POST=$(mktemp) || exit 1
OUT=$(mktemp) || exit 1
IN=README.md

$1 --dump-monsters | grep DUMP | sed 's/DUMP: //g' > $PAYLOAD
if [[ $? -ne 0 ]]; then
  exit 1
fi

sed -i 's/<newline>/<br \/>/g' $PAYLOAD
sed "1,/begin monsters type marker/!d" $IN > $PRE
sed "/end monsters type marker/,\$!d" $IN | tail -n +1 - > $POST

cat $PRE $PAYLOAD $POST > $OUT
diff $IN $OUT

if [ "$2" = "do-it" ]; then
  mv $OUT $IN
fi

exit 0
