#!/usr/bin/bash

set -x 

ROOT_DIR=$PWD
BUILD_DIR=$ROOT_DIR/build
rm -rf $BUILD_DIR > /dev/null 2>&1
mkdir -p $BUILD_DIR
cd $BUILD_DIR
cmake ../
#just show what make is attempting to do
#make -n
make -j 2 VERBOSE=1