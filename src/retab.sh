#!/bin/sh
TMP=$(mktemp)
ORIG=$(mktemp)
for FILE in *.cpp
do
    cp $FILE $ORIG
    unexpand --tabs=4 $FILE > $TMP
    expand --tabs=2 $TMP > $FILE
    diff $FILE $ORIG
done
