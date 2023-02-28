import matplotlib.pyplot as plt
import numpy as np

# N = 10 
# Hash table time: 2 microseconds
# Linear search time: 5 microseconds
# N = 100
# Hash table time: 3 microseconds
# Linear search time: 25 microseconds
# N = 1000
# Hash table time: 2 microseconds
# Linear search time: 182 microseconds
# N = 10000
# Hash table time: 3 microseconds
# Linear search time: 461 microseconds
# N = 100000
# Hash table time: 3 microseconds
# Linear search time: 2190 microseconds


# Linear search
x1 = np.array([10, 100, 1000, 10000, 100000])
y1 = np.array([2, 3, 2, 3, 3])

# Hash table time table
x2 = np.array([10, 100, 1000, 10000, 100000])
y2 = np.array([5, 25, 182, 461, 2195])

plt.xscale("log")

plt.title("Hash index vs Linear search")
plt.xlabel("Size of the input (blocks)")
plt.ylabel("Execution time (microseconds)")

plt.plot(x1, y1, marker = 's', color = 'green')
plt.plot(x2, y2, marker = 'o', color = 'blue')

plt.legend(["Hash index", "Linear search"])

plt.grid()
plt.savefig('chart1.png')