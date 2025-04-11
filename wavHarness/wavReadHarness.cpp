#include "juce_audio_basics/juce_audio_basics.h"
#include "juce_audio_formats/juce_audio_formats.h"
#include "juce_core/juce_core.h"

int readWAV(const uint8_t* data, size_t size) 
{   
    try {
        // Create a non-owning view of the data
        juce::MemoryInputStream* mis = new juce::MemoryInputStream(data, size, false);
        
        // Create format manager
        juce::AudioFormatManager formatManager;
        formatManager.registerBasicFormats();
        
        // Create reader - transfer ownership of the stream
        std::unique_ptr<juce::AudioFormatReader> reader(
            formatManager.createReaderFor(std::unique_ptr<juce::MemoryInputStream>(mis)));
        
        if (reader) 
        {
            // Create buffer and read samples
            juce::AudioBuffer<float> buffer(reader->numChannels, 
                                          (int)reader->lengthInSamples);
            reader->read(&buffer, 0, (int)reader->lengthInSamples, 0, true, true);
        }
    }
    catch (...) 
    {
        // Ignore all exceptions
    }
    
    return 0;
}

// Optional test main function
int main(int argc, char* argv[])
{
    if (argc < 2) return 1;
    
    juce::File inputFile(argv[1]);
    juce::MemoryBlock fileData;
    
    if (inputFile.loadFileAsData(fileData))
    {
        while(__AFL_LOOP(2)){
            readWAV(static_cast<const uint8_t*>(fileData.getData()), fileData.getSize());
        }
    }
    
    return 1;
}