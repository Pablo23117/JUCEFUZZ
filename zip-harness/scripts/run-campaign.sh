#!/bin/bash

# Go to harness directory
cd $HOME/Desktop/JUCEFUZZ/zip-harness/

# Build the harness without ASAN enabled
export CC=afl-clang-lto
export CXX=afl-clang-lto++

echo "=== Building MP3 harness without ASAN ==="
sudo rm -rf $HOME/Desktop/JUCEFUZZ/zip-harness/cmake-build
cmake -B cmake-build -DCMAKE_PREFIX_PATH=$HOME/Desktop/JUCEFUZZ/juce/install
cmake --build cmake-build -j $(nproc)
echo "=== ZIP harness built without ASAN ==="

echo "== Starting fuzzing session ==="
afl-fuzz -i $HOME/Desktop/JUCEFUZZ/zip-harness/in/ -o $HOME/Desktop/JUCEFUZZ/zip-harness/out/ -- $HOME/Desktop/JUCEFUZZ/zip-harness/cmake-build/JuceZipHarness_artefacts/JuceZipHarness @@
