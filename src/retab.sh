#!/bin/sh
TMP=$(mktemp)
ORIG=$(mktemp)
for FILE in *.cpp *.h
do
    cp $FILE $ORIG
    unexpand --first-only --tabs=4 $FILE > $TMP
    expand --initial --tabs=2 $TMP > $FILE
    diff $FILE $ORIG
done
