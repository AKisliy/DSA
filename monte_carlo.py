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


def get_random_sign():
    sign = random.randrange(1000) % 2
    if sign % 2 == 0:
        return -1
    return 1


def get_random_point():
    random.seed(time.time())
    x = get_random_sign() * random.random()
    y = get_random_sign() * random.random()
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
for i in range(100, 5001, 100):
    cur = montecarlo(i)
    n_array.append(i)
    pi_array.append(cur)
    delta_array.append(abs(math.pi - cur) / 100.0)
plt.subplot(211)
plt.plot(n_array, pi_array, 'b-.')
plt.subplot(212)
plt.plot(n_array, delta_array,'r--')
plt.show()

output = ["%.2f" % i for i in pi_array]
print(f"n_array = {n_array}")
print(f"pi_array = {output}")
output = ["%.6f" % i for i in delta_array]
print(f"delt_array = {output}")

