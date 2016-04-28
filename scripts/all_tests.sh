#!/bin/bash
# Fail on error
set -e

LIBS_DIR='lib'
LIBS=$(ls lib)

for lib in $LIBS; do
    make -C "$LIBS_DIR/$lib" clean
    make -C "$LIBS_DIR/$lib"
    make -C "$LIBS_DIR/$lib" test
done
