import matplotlib.pyplot as plt

x = []
y =[]

x1 = []
y1 =[]

f = open("cycle2b.txt", 'r')
for line in f:
    a, b = [int(k) for k in line.split()]
    x.append(a)
    y.append(b)

f = open("cycle1b.txt", 'r')
for line in f:
    a, b = [int(k) for k in line.split()]
    x1.append(a)
    y1.append(b)

plt.plot(x, y, 'bo', linestyle="--")
plt.plot(x1, y1, 'o', linestyle="--", color="red")
plt.title("Greedy method with cycle for kroB100.tsp")
plt.show()