import math
import random
import time
import matplotlib.pyplot as plt


class Point:
    def __init__(self, x, y):
        self.x = x
        self.y = y

    def in_circle(self):
        return (self.x * self.x + self.y * self.y) <= 1


def get_random_point():
    random.seed(time.time())
    x = random.random()
    y = random.random()
    return Point(x, y)


def montecarlo(n):
    pCircle = 0
    pSquare = n
    for i in range(n):
        point = get_random_point()
        if point.in_circle():
            pCircle += 1
    return 4.0 * (pCircle / pSquare)


n_array = []
pi_array = []
delta_array = []
pi = 3.1415926535
for i in range(100, 5000, 100):
    cur = montecarlo(i)
    n_array.append(i)
    pi_array.append(cur)
    delta_array.append(abs(math.pi - cur) / 100.0)
plt.subplot(211)
plt.plot(n_array, pi_array, 'b-.')
plt.subplot(212)
plt.plot(n_array, delta_array,'r--')
plt.show()

print(f"n_array = {n_array}")
print(f"pi_array = {pi_array}")
print(f"delt_array = {delta_array}")

