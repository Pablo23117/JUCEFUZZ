#include <juce_core/juce_core.h>
#include <juce_audio_basics/juce_audio_basics.h>
#include <juce_audio_formats/juce_audio_formats.h>
#include <iostream>

bool readWavFileExample(const char* fileName) {
    if (!fileName) {
        std::cerr << "Error: Null filename\n";
        return false;
    }

    juce::File inputFile(fileName);
    if (!inputFile.existsAsFile()) {
        std::cerr << "Error: File does not exist\n";
        return false;
    }

    juce::AudioFormatManager formatManager;
    formatManager.registerBasicFormats();

    std::unique_ptr<juce::AudioFormatReader> reader(formatManager.createReaderFor(inputFile));
    if (!reader) {
        std::cerr << "Error: Unsupported or corrupt audio file\n";
        return false;
    }

    if (reader->numChannels <= 0 || reader->sampleRate <= 0) {
        std::cerr << "Error: Invalid audio metadata\n";
        return false;
    }

    const int maxSamplesToProcess = 48000 * 5;  // 5 seconds at 48kHz
    const int numSamples = std::min(static_cast<int>(reader->lengthInSamples), maxSamplesToProcess);
    if (numSamples <= 0) {
        std::cerr << "Error: File contains no samples\n";
        return false;
    }

    juce::AudioBuffer<float> buffer(reader->numChannels, numSamples);
    reader->read(&buffer, 0, numSamples, 0, true, true);

    printf("made it all the way here");
    return true;
}

int main(int argc, char* argv[]) {
    while (__AFL_LOOP(1000)) {
        readWavFileExample(argv[1]);
    }
    return 0;
}