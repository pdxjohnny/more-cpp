#!/bin/bash

TMP_FILE=/tmp/test-headers
HEADER='test/info.h'
FILES=$(find test -type f | grep -v 'info.')

cat $FILES | grep 'int test_' | sed 's/ {/;/g' > $TMP_FILE
while read func; do
    grep -Fxq "$func" $HEADER
    if [ $? -eq 1 ]; then
        echo Adding... $func
        echo $func >> $HEADER
    fi
done < $TMP_FILE
rm $TMP_FILE

