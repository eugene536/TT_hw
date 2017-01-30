#!/bin/bash
rm -rf build
mkdir build
cd build
GTEST=y cmake ../
GTEST=y make
cd ..

