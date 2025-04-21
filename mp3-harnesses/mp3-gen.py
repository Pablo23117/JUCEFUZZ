from pydub import AudioSegment
from pydub.generators import Sine
import io

# Create a silent audio segment (1 second of silence)
# audio = AudioSegment.silent(duration=1000)  # duration in milliseconds

# Alternatively, create a tone (uncomment to use instead of silence)
audio = Sine(440).to_audio_segment(duration=1000)  # 440Hz tone for 1 second

# Export to MP3 with very low quality to minimize file size
buffer = io.BytesIO()
audio.export(buffer, format="mp3", bitrate="8k")  # Extremely low bitrate

# Ensure the file is exactly 1KB (1024 bytes)
mp3_data = buffer.getvalue()[:1024]

# Save to file
with open("output_1kb.mp3", "wb") as f:
    f.write(mp3_data)