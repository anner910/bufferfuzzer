#!/bin/sh

git clone  https://gitee.com/anner910/bufferfuzzer.git


cd bufferfuzzer

mkdir build

cd build

cmake ..

make  

echo "cp libbufferfuzzer.so" 

cp libbufferfuzzer.so ../../

echo "cp bufferfuzzer.h" 

cp ../bufferfuzzer/bufferfuzzer.h ../../

cd ../../

rm -rf bufferfuzzer/