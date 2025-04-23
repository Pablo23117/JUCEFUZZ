#include "juce_core/juce_core.h"
#include <cstdlib>

// Persistent mode setup
__AFL_FUZZ_INIT();

int zip_harness(const uint8_t* data, size_t size) 
{
    try 
    {
        juce::MemoryBlock memBlock(size);
        memcpy(memBlock.getData(), data, size);

        auto in_stream = std::make_unique<juce::MemoryInputStream>(memBlock.getData(), size, false);
        juce::ZipFile test_zip(*in_stream);
        auto test_target_dir = juce::File::getSpecialLocation(juce::File::tempDirectory).getChildFile("unzipTest");

        if (!test_target_dir.exists())
            test_target_dir.createDirectory();

        auto result = test_zip.uncompressTo(test_target_dir);

        for (int i = 0; i < test_zip.getNumEntries(); i++)
        {
            auto entry = test_zip.getEntry(i);
            juce::File extracted_file = test_target_dir.getChildFile(entry->filename);
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

    unsigned char *buf = __AFL_FUZZ_TESTCASE_BUF;

    // const char* asan_enabled = std::getenv("AFL_USE_ASAN");
    // if (asan_enabled && std::string(asan_enabled) == "1") 
    // {
    //     int len = __AFL_FUZZ_TESTCASE_LEN;
    //     zip_harness(buf, len);
    //     delete buf;
    // } else 
    // {
    //     while (__AFL_LOOP(5000)) 
    //     {
    //         int len = __AFL_FUZZ_TESTCASE_LEN;
    //         zip_harness(buf, len);
    //         buf = __AFL_FUZZ_TESTCASE_BUF;
    //     }

    //     delete buf;
    // }

    while (__AFL_LOOP(5000)) 
    {
        int len = __AFL_FUZZ_TESTCASE_LEN;
        zip_harness(buf, len);
        buf = __AFL_FUZZ_TESTCASE_BUF;
    }

    delete buf;
    return 0;
}