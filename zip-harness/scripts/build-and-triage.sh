#!/bin/bash

# Go to JUCE library
cd $HOME/Desktop/JUCEFUZZ/juce

# Set up env variables
export AFL_USE_ASAN=1
export CC=clang
export CXX=clang++

# Build the JUCE library with ASAN enabled
echo "=== Building JUCE with ASAN ==="
sudo rm -rf $HOME/Desktop/JUCEFUZZ/juce/cmake-build-install
AFL_USE_ASAN=1 cmake -B cmake-build-install -DCMAKE_CXX_FLAGS="-fsanitize=address -g -fno-omit-frame-pointer" -DCMAKE_BUILD_TYPE=Debug -DCMAKE_INSTALL_PREFIX=$HOME/Desktop/JUCEFUZZ/juce/install
AFL_USE_ASAN=1 cmake --build cmake-build-install --target install -j $(nproc)
echo "=== JUCE built with ASAN ==="

# Go to harness directory
cd $HOME/Desktop/JUCEFUZZ/zip-harness/

# Build the harness with ASAN enabled
export AFL_USE_ASAN=1
export CC=clang
export CXX=clang++

echo "=== Building MP3 harness with ASAN ==="
sudo rm -rf $HOME/Desktop/JUCEFUZZ/zip-harness/cmake-build
AFL_USE_ASAN=1 cmake -B cmake-build -DCMAKE_CXX_FLAGS="-fsanitize=address -g -fno-omit-frame-pointer" -DCMAKE_BUILD_TYPE=Debug -DCMAKE_PREFIX_PATH=$HOME/Desktop/JUCEFUZZ/juce/install
AFL_USE_ASAN=1 cmake --build cmake-build -j $(nproc)
echo "=== MP3 harness built with ASAN ==="

# Triage Crashes
echo "=== Triaging each crash found with AFL++ ==="
for crash in $HOME/Desktop/JUCEFUZZ/zip-harness/out/default/crashes/id:*; do
  echo "==== Testing $crash ===="
  $HOME/Desktop/JUCEFUZZ/zip-harness/cmake-build/JuceZipHarness_artefacts/Debug/JuceZipHarness < "$crash"
done
