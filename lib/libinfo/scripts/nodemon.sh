#!/bin/bash

ln -s makefile makefile.make
nodemon -e c,cpp,h,make --exec 'clear; make clean && make && make test; exit 0'

