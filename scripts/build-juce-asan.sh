#!/bin/bash

# Go to JUCE library
cd $HOME/Desktop/JUCEFUZZ/juce

# Set up env variables
export AFL_USE_ASAN=1
export CC=afl-clang-lto
export CXX=afl-clang-lto++

# Build the JUCE library with ASAN enabled
echo "=== Building JUCE with ASAN ==="
sudo rm -rf $HOME/Desktop/JUCEFUZZ/juce/cmake-build-install
AFL_USE_ASAN=1 cmake -B cmake-build-install -DCMAKE_CXX_FLAGS="-fsanitize=address -g -fno-omit-frame-pointer" -DCMAKE_BUILD_TYPE=Debug -DCMAKE_INSTALL_PREFIX=$HOME/Desktop/JUCEFUZZ/juce/install
AFL_USE_ASAN=1 cmake --build cmake-build-install --target install
echo "=== JUCE built with ASAN ==="