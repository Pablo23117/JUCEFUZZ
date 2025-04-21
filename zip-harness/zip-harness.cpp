#include "juce_core/juce_core.h"
#include <cstdlib>

// Persistent mode setup
#ifdef __AFL_COMPILER
  __AFL_FUZZ_INIT();
#endif

int readMP3(const uint8_t* data, size_t size) 
{
    try 
    {
        juce::MemoryBlock memBlock(size);
        memcpy(memBlock.getData(), data, size);

        auto in_stream = std::make_unique<juce::MemoryInputStream>(memBlock, size, false);
        juce::ZipFile zip()
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

    unsigned char *buf = __AFL_FUZZ_TESTCASE_BUF;

    const char* asan_enabled = std::getenv("AFL_USE_ASAN");
    if (asan_enabled && std::string(asan_enabled) == "1") 
    {
        int len = __AFL_FUZZ_TESTCASE_LEN;
        readMP3(buf, len);
        delete buf;
    } else 
    {
        while (__AFL_LOOP(5000)) 
        {
            int len = __AFL_FUZZ_TESTCASE_LEN;
            readMP3(buf, len);
            buf = __AFL_FUZZ_TESTCASE_BUF;
        }

        delete buf;
    }
    return 0;
}