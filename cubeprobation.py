import random
from enum import Enum
import matplotlib.pyplot as plt


class Probation(Enum):
    SQUARE = 0
    CUBE = 1


class HashTable:
    def __init__(self, size: int, p: Probation, coeffs):
        self.size = size
        self.probation = p
        self.occupied = [False] * size
        self.table = [0] * size
        if self.probation == Probation.SQUARE and len(coeffs) < 2:
            self.coeffs = [0.5, 0.5]
        elif self.probation == Probation.CUBE and len(coeffs) < 3:
            self.coeffs = [1, 1, 1]
        self.coeffs = coeffs
        self.totalProbations = 0
        self.collisions = 0

    def insert(self, val: int):
        index = self.hash(val)
        for i in range(0, self.size):
            self.totalProbations += 1
            if self.probation == Probation.SQUARE:
                index = int(index + self.coeffs[0] * i + self.coeffs[1] * i * i) % self.size;
            else:
                index = int(index + self.coeffs[0] * i +
                            self.coeffs[1] * i * i + self.
                            coeffs[2] * i * i * i) % self.size
            if not self.occupied[index]:
                break
        if self.occupied[index]:
            self.collisions += 1
        self.table[index] = val
        self.occupied[index] = True

    def hash(self, val: int):
        return abs(val) % self.size


# information for plot
X = []
sqY = []
cbY = []
# count of tests for each size
testsCnt = 10
# iterate over different sizes to compare square and cube probations
for size in range(1000, 10001, 1000):
    sqTest = []
    cubeTest = []
    for tests in range(0, testsCnt):
        sq = HashTable(size, Probation.SQUARE, [0.5, 0.5])
        cb = HashTable(size, Probation.CUBE, [1, 1, 1])
        for i in range(0, size):
            val = random.randint(0, 1000000)
            sq.insert(val)
            cb.insert(val)
        sqTest.append(sq.totalProbations)
        cubeTest.append(cb.totalProbations)
    X.append(size)

    sqY.append(sum(sqTest) / testsCnt)

    cbY.append(sum(cubeTest) / testsCnt)

# draw the plot
y = sqY
z = cbY

plt.plot(X, y, color='r', label='square')
plt.plot(X, z, color='g', label='cube')

plt.xlabel("Table size")
plt.ylabel("Probations")
plt.title("Compare square and cube probations")

plt.legend()

plt.show()
