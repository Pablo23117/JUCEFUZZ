import wave
import struct

# Settings
sample_rate = 44100  # JUCE often expects 44.1kHz
duration = 0.1       # 100ms (short but not too minimal)
channels = 2         # Stereo (JUCE handles mono/stereo)
sampwidth = 2        # 16-bit (JUCE prefers this over 8-bit)

# Generate silence (16-bit stereo)
num_samples = int(sample_rate * duration)
silent_data = b'\x00\x00' * channels * num_samples  # 16-bit silence (0)

# Write WAV file
with wave.open("valid.wav", "wb") as wav_file:
    wav_file.setnchannels(channels)
    wav_file.setsampwidth(sampwidth)
    wav_file.setframerate(sample_rate)
    wav_file.writeframes(silent_data)