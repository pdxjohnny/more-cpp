#!/bin/bash

ln -s makefile makefile.make
nodemon -e c,cpp,h,make --exec 'clear; make clean && scan-build make -e && make test; exit 0'

