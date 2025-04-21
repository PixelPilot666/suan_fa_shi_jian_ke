import subprocess
import re
import statistics

file = "points_103.txt"
thresholds = [5, 50, 500]

# files = ["points_103.txt", "points_104.txt", "points_105.txt"]
# threshold = 5

runs = 100  # Number of runs for each file

for threshold in thresholds:
# for file in files:
    print(f"Testing threshold: {file}")
    times = []
    
    for i in range(1, runs + 1):
        result = subprocess.run(["search.exe", file, str(threshold)], 
                               capture_output=True, text=True)
        output = result.stdout
        time_match = re.search(r"Time used: ([\d.]+) ms", output)
        if time_match:
            time = float(time_match.group(1))
            times.append(time)
            print(f"Run {i}: {time} ms")
    
    avg = statistics.mean(times)
    print(f"Average execution time for {file} with threshold {threshold}: {avg} ms")
    print("-" * 40)