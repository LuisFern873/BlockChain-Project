import matplotlib.pyplot as plt
import numpy as np

# N = 10 
# B+ tree time: 1 microseconds
# Linear search time: 205 microseconds
# N = 100
# B+ tree time: 3 microseconds
# Linear search time: 2625 microseconds
# N = 1000
# B+ tree time: 9 microseconds
# Linear search time: 2308 microseconds
# N = 10000
# B+ tree time: 84 microseconds
# Linear search time: 29229 microseconds
# N = 100000
# B+ tree time: 405 microseconds
# Linear search time: 211980 microseconds


# Linear search
x1 = np.array([10, 100, 1000, 10000, 100000])
y1 = np.array([1, 3, 9, 84, 405])

# B+ tree time table
x2 = np.array([10, 100, 1000, 10000, 100000])
y2 = np.array([205, 2625, 2308, 29229, 211980])

plt.xscale("log")

plt.title("B+ Tree index vs Linear search")
plt.xlabel("Size of the input (blocks)")
plt.ylabel("Execution time (microseconds)")

plt.plot(x1, y1, marker = 's', color = 'orange')
plt.plot(x2, y2, marker = 'o', color = 'blue')

plt.legend(["B+ Tree index", "Linear search"])

plt.grid()
plt.savefig('chart2.png') 