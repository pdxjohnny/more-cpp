#!/bin/bash

ln -s makefile makefile.make
nodemon -e c,cpp,h,make --exec 'clear; make; exit 0'

