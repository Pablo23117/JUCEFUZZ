#include "juce_audio_basics/juce_audio_basics.h"
#include "juce_audio_formats/juce_audio_formats.h"
#include "juce_core/juce_core.h"

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
    // AFL++ persistent mode
    __AFL_INIT();
    unsigned char *buf = __AFL_FUZZ_TESTCASE_BUF;
    
    while (__AFL_LOOP(100)) {
        int len = __AFL_FUZZ_TESTCASE_LEN;
        readWAV(buf, len);
    }
    return 0;
}