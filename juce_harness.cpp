#include <juce_core/juce_core.h>
#include <fstream>
#include <string>
#include <stdio.h>

// Entry point for AFL++ fuzzing
int main(int argc, char *argv[]) 
{
    // FILE* f = fopen(argv[1], "r");

    // // Determine file size
    // fseek(f, 0, SEEK_END);
    // size_t size = ftell(f);

    // char* where = new char[size];

    // rewind(f);
    // fread(where, sizeof(char), size, f);

    std::ifstream file(argv[1]);
    std::string str; 
    while (std::getline(file, str))
    {
        // Process str
    }

    // Convert fuzzer input to a JUCE String
    juce::String inputString(str);

    // Perform operations on the String
    juce::String upperCaseString = inputString.toUpperCase();

    juce::File juceFile(inputString);
    // delete[] where;

    return 0; // Indicate successful execution
}