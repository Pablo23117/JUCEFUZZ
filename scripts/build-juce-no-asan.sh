#!/bin/bash

# Go to JUCE library
cd $HOME/Desktop/JUCEFUZZ/juce

# Set up env variables
export CC=afl-clang-lto
export CXX=afl-clang-lto++

# Build the JUCE library without ASAN enabled
echo "=== Building JUCE without ASAN ==="
sudo rm -rf $HOME/Desktop/JUCEFUZZ/juce/cmake-build-install
cmake -B cmake-build-install -DCMAKE_INSTALL_PREFIX=$HOME/Desktop/JUCEFUZZ/juce/install
cmake --build cmake-build-install --target install -j $(nproc)
echo "=== JUCE built without ASAN ==="