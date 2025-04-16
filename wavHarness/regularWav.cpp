#include "juce_audio_basics/juce_audio_basics.h"
#include "juce_audio_formats/juce_audio_formats.h"
#include "juce_core/juce_core.h"

// AFL++ persistent mode headers
#ifdef __AFL_COMPILER
#endif

int readWAV(const uint8_t* data, size_t size) 
{
    try {
        // Create input stream from memory
        juce::MemoryInputStream* raw_mis = new juce::MemoryInputStream(data, size, false);
        std::unique_ptr<juce::InputStream> mis(raw_mis);
        
        // Setup audio format manager
        juce::AudioFormatManager formatManager;
        formatManager.registerBasicFormats();
        
        // Create reader (transfers ownership of the stream)
        std::unique_ptr<juce::AudioFormatReader> reader(
            formatManager.createReaderFor(std::move(mis)));
        
        if (reader) {
            juce::AudioBuffer<float> buffer(
                reader->numChannels,
                static_cast<int>(reader->lengthInSamples));
            
            reader->read(
                &buffer,
                0,
                static_cast<int>(reader->lengthInSamples),
                0,
                true,
                true);
        }
    }
    catch (...) {
        return -1; // Error code for failures
    }
    
    return 0;
}

int main(int argc, char* argv[])
{
    // Fallback for non-fuzzing compilation
    if (argc < 2) return 1;
    
    juce::File inputFile(argv[1]);
    juce::MemoryBlock fileData;
    
    if (inputFile.loadFileAsData(fileData)) {
        readWAV(static_cast<const uint8_t*>(fileData.getData()),
                fileData.getSize());
    }
    return 0;
}