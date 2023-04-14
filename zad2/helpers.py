import numpy as np
import matplotlib.pyplot as plt


def load_file(filename: str):
    f = open(filename, "r")
    graph = np.empty((0, 3), int)
    for line in f:
        graph = np.append(graph, np.array([[int(x) for x in line.split(" ")]]), axis=0)
    return graph


def euclidean_distance(a: np.ndarray, b: np.ndarray):
    return np.sqrt(np.sum(np.square(np.subtract(a, b))))


def create_distance_matrix(graph: np.ndarray):
    distance_matrix = np.zeros((graph.shape[0], graph.shape[0]))
    for x, y in np.ndindex(distance_matrix.shape):
        distance_matrix[x, y] = euclidean_distance(graph[x, 1:], graph[y, 1:])
    return distance_matrix


def check_length(graph: np.ndarray, distance_matrix: np.ndarray):
    length = 0
    for x in range(1, len(graph)):
        length += distance_matrix[graph[x], graph[x - 1]]
    return length


def change_of_length(
    first_vertex: int, second_vertex: int, new_vertex: int, distance_matrix: np.ndarray
):
    return (
        distance_matrix[first_vertex, new_vertex]
        + distance_matrix[second_vertex, new_vertex]
        - distance_matrix[first_vertex, second_vertex]
    )


def plot(first_cycle: np.ndarray, second_cycle: np.ndarray, graph: np.ndarray):
    x1 = []
    y1 = []
    x2 = []
    y2 = []
    for vertex in first_cycle:
        x1.append(graph[vertex, 1])
        y1.append(graph[vertex, 2])

    for vertex in second_cycle:
        x2.append(graph[vertex, 1])
        y2.append(graph[vertex, 2])

    plt.plot(x1, y1, "bo", linestyle="--")
    plt.plot(x2, y2, "o", linestyle="--", color="red")
    plt.title("Greedy cycle")
    plt.show()
