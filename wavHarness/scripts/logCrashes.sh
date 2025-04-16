log_file="replay_log.txt"

# Loop through each crash file in the crashes directory
for crash_file in ./../out/default/allCrashes/*; do
  echo "Replaying: $crash_file" >> "$log_file"

  # Run the fuzzgoat_ASAN binary, append the output to the log file
  ./../build-asan/JuceHarness_artefacts/Debug/JuceHarness $crash_file >> "$log_file" 2>&1  #both stdout and stderr to the log file
  echo >> "$log_file"
done

