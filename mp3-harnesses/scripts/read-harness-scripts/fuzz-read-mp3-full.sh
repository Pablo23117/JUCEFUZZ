#!/bin/bash

# Go to JUCE library
cd $HOME/Desktop/JUCEFUZZ/juce

# Set up env variables
export AFL_USE_ASAN=1
export CC=afl-clang-lto
export CXX=afl-clang-lto++

# Build the JUCE library without ASAN enabled
echo "=== Building JUCE without ASAN ==="
sudo rm -rf $HOME/Desktop/JUCEFUZZ/juce/cmake-build-install
cmake -B cmake-build-install -DCMAKE_INSTALL_PREFIX=$HOME/Desktop/JUCEFUZZ/juce/install
cmake --build cmake-build-install --target install -j $(nproc)
echo "=== JUCE built without ASAN ==="

# Go to harness directory
cd $HOME/Desktop/JUCEFUZZ/mp3-harness/read-harness/

# Build the harness without ASAN enabled
export AFL_USE_ASAN=1
export CC=afl-clang-lto
export CXX=afl-clang-lto++

echo "=== Building MP3 harness without ASAN ==="
sudo rm -rf $HOME/Desktop/JUCEFUZZ/mp3-harness/read-harness/cmake-build
cmake -B cmake-build -DCMAKE_PREFIX_PATH=$HOME/Desktop/JUCEFUZZ/juce/install
cmake --build cmake-build -j $(nproc)
echo "=== MP3 harness built without ASAN ==="

echo "== Starting fuzzing session ==="
afl-fuzz -i $HOME/Desktop/JUCEFUZZ/mp3-harness/read-harness/in/ -o $HOME/Desktop/JUCEFUZZ/mp3-harness/read-harness/out/ -- $HOME/Desktop/JUCEFUZZ/mp3-harness/read-harness/cmake-build/JuceMP3ReadHarness_artefacts/JuceMP3ReadHarness @@
