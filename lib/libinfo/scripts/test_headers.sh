#!/bin/bash

TMP_HEADER_FILE=test-headers
TMP_MAIN_FILE=test-main
HEADER='test/info.h'
MAIN='test/info.cpp'
FILES=$(find test -type f | grep -v 'info.')

exec 3<>$MAIN
while read line; do
    echo -e $line >> $TMP_MAIN_FILE
    echo $line | grep -q "int main"
    if [ $? -eq 0 ]; then
        break
    fi
done <&3

cat $FILES | grep 'int test_'  | grep -v 'Binary file' | sed 's/ {/;/g' > $TMP_HEADER_FILE
while read func; do
    grep -q "$func" $HEADER
    if [ $? -eq 1 ]; then
        echo Adding... $func to $HEADER
        echo $func >> $HEADER
    fi
    func=$(echo $func | sed 's/int //g' | sed 's/;//g' | sed 's/()//g')
    grep -q "$func" $MAIN
    if [ $? -eq 1 ]; then
        echo Adding... $func to $MAIN
        echo -e "MACRO_TEST($func);" >> $TMP_MAIN_FILE
    fi
done < $TMP_HEADER_FILE
rm $TMP_HEADER_FILE

while read line; do
    echo $line >> $TMP_MAIN_FILE
done <&3

3<&-
cp $TMP_MAIN_FILE $MAIN
rm $TMP_MAIN_FILE

