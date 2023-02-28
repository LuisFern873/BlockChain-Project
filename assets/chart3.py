import matplotlib.pyplot as plt
import numpy as np

# N = 10 
# Trie time: 2 microseconds
# Linear search time: 194 microseconds
# N = 100
# Trie time: 4 microseconds
# Linear search time: 156 microseconds
# N = 1000
# Trie time: 32 microseconds
# Linear search time: 2863 microseconds
# N = 10000
# Trie time: 45 microseconds
# Linear search time: 6388 microseconds
# N = 100000
# Trie time: 118 microseconds
# Linear search time: 18012 microseconds


# Linear search
x1 = np.array([10, 100, 1000, 10000, 100000])
y1 = np.array([2, 4, 32, 45, 118])

# Trie time table
x2 = np.array([10, 100, 1000, 10000, 100000])
y2 = np.array([194, 156, 2863, 6388, 18012])

plt.xscale("log")

plt.title("Trie index vs Linear search")
plt.xlabel("Size of the input (blocks)")
plt.ylabel("Execution time (microseconds)")

plt.plot(x1, y1, marker = 's', color = 'yellow')
plt.plot(x2, y2, marker = 'o', color = 'blue')

plt.legend(["Trie index", "Linear search"])

plt.grid()
plt.savefig('chart3.png')