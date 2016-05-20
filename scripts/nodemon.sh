#!/bin/bash

if [ -z "$NODEMON_POST" ]; then
    NODEMON_POST='test'
fi

ln -s makefile makefile.make
nodemon -e c,cpp,h,make --exec "clear; make -e clean && make -e -j && make -e test; $NODEMON_POST; exit 0"

