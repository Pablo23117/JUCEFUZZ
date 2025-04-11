#include "juce_audio_basics/juce_audio_basics.h"
#include "juce_audio_formats/juce_audio_formats.h"
#include "juce_core/juce_core.h"

class WavFileReader
{
public:
    struct AudioFileInfo {
        double sampleRate;
        int numChannels;
        juce::int64 numSamples;
        int bitDepth;
        juce::String audioFormat;
    };

    // Read audio file and return its contents in an AudioBuffer
    std::unique_ptr<juce::AudioBuffer<float>> readFile(const juce::File& audioFile, AudioFileInfo* outInfo = nullptr)
    {
        if (!audioFile.existsAsFile())
        {
            juce::Logger::writeToLog("File doesn't exist: " + audioFile.getFullPathName());
            return nullptr;
        }

        // Create an audio format manager and register wav format
        juce::AudioFormatManager formatManager;
        formatManager.registerBasicFormats(); // This registers WAV, AIFF, and a few others

        // Create a reader for the file
        std::unique_ptr<juce::AudioFormatReader> reader(formatManager.createReaderFor(audioFile));
        
        if (reader == nullptr)
        {
            juce::Logger::writeToLog("Couldn't create reader for file: " + audioFile.getFullPathName());
            return nullptr;
        }

        // Fill out info structure if requested
        if (outInfo != nullptr)
        {
            outInfo->sampleRate = reader->sampleRate;
            outInfo->numChannels = (int)reader->numChannels;
            outInfo->numSamples = reader->lengthInSamples;
            outInfo->bitDepth = (int)reader->bitsPerSample;
            outInfo->audioFormat = reader->getFormatName();
        }

        // Create an audio buffer to hold the file contents
        auto buffer = std::make_unique<juce::AudioBuffer<float>>(reader->numChannels, (int)reader->lengthInSamples);

        // Read the file into the buffer
        if (!reader->read(buffer.get(), 0, (int)reader->lengthInSamples, 0, true, true))
        {
            juce::Logger::writeToLog("Failed to read audio data from file: " + audioFile.getFullPathName());
            return nullptr;
        }

        return buffer;
    }
};

int main(int argc, char* argv[])
{   
    // Example usage:
    juce::File inputFile(argv[1]); // Change this to your WAV file path
    
    WavFileReader::AudioFileInfo fileInfo;
    WavFileReader reader;
    auto audioBuffer = reader.readFile(inputFile, &fileInfo);
    
    if (audioBuffer != nullptr)
    {
        // Access the audio data (example: print first 10 samples of first channel)
        const float* channelData = audioBuffer->getReadPointer(0);
        juce::String sampleStr = "First 10 samples: ";
        for (int i = 0; i < 10 && i < audioBuffer->getNumSamples(); ++i)
        {
            sampleStr += juce::String(channelData[i], 4) + " ";
        }
        juce::Logger::writeToLog(sampleStr);
    }
    else
    {
        juce::Logger::writeToLog("Failed to read WAV file");
    }
    
    return 0;
}