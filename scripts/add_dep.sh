#!/bin/bash

if [ $# -ne 1 ]; then
    echo "Usage: $0 libexample"
    exit 1
fi

mkdir -p deps
cd deps
ln -s "../../../lib/$1" $1
cd ..

