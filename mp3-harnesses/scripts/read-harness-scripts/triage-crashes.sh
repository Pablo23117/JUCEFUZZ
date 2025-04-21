#!/bin/bash

# Go to harness directory
cd $HOME/Desktop/JUCEFUZZ/mp3-harnesses/read-harness/

# Build the harness with ASAN enabled
export AFL_USE_ASAN=1
export CC=clang
export CXX=clang++

echo "=== Building MP3 harness with ASAN ==="
sudo rm -rf $HOME/Desktop/JUCEFUZZ/mp3-harness/read-harness/cmake-build
AFL_USE_ASAN=1 cmake -B cmake-build -DCMAKE_CXX_FLAGS="-fsanitize=address -g -fno-omit-frame-pointer" -DCMAKE_BUILD_TYPE=Debug -DCMAKE_PREFIX_PATH=$HOME/Desktop/JUCEFUZZ/juce/install
AFL_USE_ASAN=1 cmake --build cmake-build -j $(nproc)
echo "=== MP3 harness built with ASAN ==="

# Triage Crashes
echo "=== Triaging each crash found with AFL++ ==="
for crash in $HOME/Desktop/JUCEFUZZ/mp3-harnesses/read-harness/out/default/crashes/id:*; do
  echo "==== Testing $crash ===="
  $HOME/Desktop/JUCEFUZZ/mp3-harnesses/read-harness/cmake-build/JuceMP3Harness_artefacts/Debug/JuceMP3Harness < "$crash"
done