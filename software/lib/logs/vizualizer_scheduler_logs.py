import pandas as pd
import matplotlib.pyplot as plt
import os

log_path = "scheduler_log.csv"

if not os.path.exists(log_path):
    print("[ERROR] Log file not found!")
    exit(1)

# Read the CSV with known columns
df = pd.read_csv(log_path, names=["timestamp", "task_id", "priority", "event"])

# Convert types
df["timestamp"] = pd.to_numeric(df["timestamp"], errors="coerce")
df["task_id"] = pd.to_numeric(df["task_id"], errors="coerce")
df["priority"] = pd.to_numeric(df["priority"], errors="coerce")
df["event"] = df["event"].astype(str)

# Drop rows with any parsing issues
df.dropna(inplace=True)

# Plot: task execution timeline
plt.figure(figsize=(12, 6))
scatter = plt.scatter(
    df["timestamp"],
    df["task_id"],
    c=df["priority"],
    cmap="viridis",
    s=80,
    alpha=0.7,
    label=df["event"]
)

plt.colorbar(scatter, label="Task Priority")
plt.xlabel("Time (ms)")
plt.ylabel("Task ID")
plt.title("Task Execution Timeline")
plt.grid(True)
plt.tight_layout()
plt.show()
