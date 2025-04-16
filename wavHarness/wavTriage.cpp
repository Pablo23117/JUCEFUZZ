#include "juce_audio_basics/juce_audio_basics.h"
#include "juce_audio_formats/juce_audio_formats.h"
#include "juce_core/juce_core.h"
#include <fstream>
#include <vector>
#include <cstdint>

// Persistent mode setup
#ifdef __AFL_COMPILER
  __AFL_FUZZ_INIT();
#endif

int readWAV(const uint8_t* data, size_t size)
{
    try {
        auto mis = std::make_unique<juce::MemoryInputStream>(data, size, false);
        juce::AudioFormatManager formatManager;
        formatManager.registerBasicFormats();

        std::unique_ptr<juce::AudioFormatReader> reader(
            formatManager.createReaderFor(std::move(mis)));

        if (reader) {
            juce::AudioBuffer<float> buffer(reader->numChannels,
                                          (int)reader->lengthInSamples);
            reader->read(&buffer, 0, (int)reader->lengthInSamples, 0, true, true);
        }
    }
    catch (...) {
        return -1; // Error code for failures
    }

    return 0;
}

int main(int argc, char* argv[])
{
    if (argc < 2)
        return 1;

    std::ifstream file(argv[1], std::ios::binary | std::ios::ate);
    if (!file)
        return 1;

    std::streamsize size = file.tellg();
    file.seekg(0, std::ios::beg);

    std::vector<uint8_t> buffer(size);
    if (!file.read((char*)buffer.data(), size))
        return 1;

    readWAV(buffer.data(), buffer.size());
    return 0;
}

