#!/bin/bash
cd build
rm -rf *
GTEST=y cmake ../
GTEST=y make
cd ..

