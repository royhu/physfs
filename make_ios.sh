#!/bin/bash

mkdir -p build_ios && cd build_ios
cmake -DCMAKE_TOOLCHAIN_FILE=../cmake/iOS.cmake  -GXcode ../

cd ..
cmake --build build_ios --config Release
