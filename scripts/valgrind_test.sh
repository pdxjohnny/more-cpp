#!/bin/bash

OLD=$PWD
cd ../

for i in $(ls); do
    cd $i
    valgrindl ./bin/*-test
    cd ..
done

cd $OLD
