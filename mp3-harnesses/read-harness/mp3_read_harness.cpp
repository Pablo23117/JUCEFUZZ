#include "juce_audio_basics/juce_audio_basics.h"
#include "juce_audio_formats/juce_audio_formats.h"
#include "juce_core/juce_core.h"
#include <cstdlib>

// Persistent mode setup
#ifdef __AFL_COMPILER
  __AFL_FUZZ_INIT();
#endif

int zip_harness(const uint8_t* data, size_t size) 
{
    try 
    {
        // Allocate memory using HeapBlock
        juce::HeapBlock<uint8_t> heapBlock(size);
        std::memcpy(heapBlock.getData(), data, size); // Copy input data to HeapBlock

        auto mis = std::make_unique<juce::MemoryInputStream>(heapBlock.getData(), size, false);
        juce::AudioFormatManager formatManager;
        formatManager.registerBasicFormats();
        
        std::unique_ptr<juce::AudioFormatReader> reader(formatManager.createReaderFor(std::move(mis)));
        
        if (reader) 
        {
            juce::AudioBuffer<float> buffer(reader->numChannels, (int)reader->lengthInSamples);
            reader->read(&buffer, 0, (int)reader->lengthInSamples, 0, true, true);
        }
    }
    catch (...) 
    {
        return -1; // Error code for failures
    }
    
    return 0;
}

int main(int argc, char* argv[])
{   

    #ifdef __AFL_HAVE_MANUAL_CONTROL
        __AFL_INIT();
    #endif

    const char* asan_enabled = std::getenv("AFL_USE_ASAN");
    if (asan_enabled && std::string(asan_enabled) == "1") 
    {
        unsigned char *buf = __AFL_FUZZ_TESTCASE_BUF;
        int len = __AFL_FUZZ_TESTCASE_LEN;
        zip_harness(buf, len);
        delete buf;
    } else 
    {
        unsigned char *buf = __AFL_FUZZ_TESTCASE_BUF;
        while (__AFL_LOOP(5000)) 
        {
            int len = __AFL_FUZZ_TESTCASE_LEN;
            zip_harness(buf, len);
            buf = __AFL_FUZZ_TESTCASE_BUF;
        }

        delete buf;
    }

    // while (__AFL_LOOP(5000)) 
    // {
    //     int len = __AFL_FUZZ_TESTCASE_LEN;
    //     zip_harness(buf, len);
    //     buf = __AFL_FUZZ_TESTCASE_BUF;
    // }
    return 0;
}