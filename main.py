import matplotlib.pyplot as plt

x = []
y =[]

x1 = []
y1 =[]

f = open("src/between_greedy1.txt", 'r')
for line in f:
    a, b = [int(k) for k in line.split()]
    x.append(a)
    y.append(b)
x.append(x[0])
y.append(y[0])
f = open("src/between_greedy2.txt", 'r')
for line in f:
    a, b = [int(k) for k in line.split()]
    x1.append(a)
    y1.append(b)

plt.plot(x, y, 'bo', linestyle="--")
plt.plot(x1, y1, 'o', linestyle="--", color="red")
plt.title("Greedy local search z wymianą wierzchołków pomiędzy cyklami")
plt.show()