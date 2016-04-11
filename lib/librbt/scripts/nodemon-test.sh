#!/bin/bash

ln -s makefile makefile.make
nodemon -e c,cpp,h,make --exec 'clear; make clean && make && ./bin/rbt-test; exit 0'

