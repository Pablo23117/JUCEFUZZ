I built JUCE inside the project folder as a sub-directory. If you are using JUCE globally, make sure to modify CMake:
	# find_package(JUCE CONFIG REQUIRED)        # If you've installed JUCE to your system
	# or
	# add_subdirectory(JUCE)                    # If you've put JUCE in a subdirectory called JUCE

To run a fuzzing campaign follow the below steps:

	1. change target_sources in CMake to wavReadHarness.cpp

	1. cmake -B build -DCMAKE_C_COMPILER=$HOME/fuzzing/AFLplusplus/afl-clang-fast -DCMAKE_CXX_COMPILER=$HOME/fuzzing/AFLplusplus/afl-clang-fast++
	
	2. cmake --build build
	
	3. afl-fuzz -i in/ -o out/ -- ./build/JuceHarness_artefacts/JuceHarness @@


To triage results from above or to triage results from a different campaign, copy output folder (needs to be named 'out') to the wavHarness directory and follow below steps.
	
	1. change target_sources in CMake to wavTriage.cpp

	2. cmake -B build-asan -DCMAKE_C_COMPILER=clang -DCMAKE_CXX_COMPILER=clang++ -DCMAKE_CXX_FLAGS="-fsanitize=address -g" -DCMAKE_BUILD_TYPE=Debug

	3. cmake --build build-asan

	4. in 'out' folder used for campaign, copy all crash input to a folder named 'allCrashes' at the same level. Make sure not to copy the README.

	5. in scripts directory, run: bash logCrashes.sh

	6. ASAN output should be in a file named replay_log.txt in the scripts folder
