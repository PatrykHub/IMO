import numpy as np
import matplotlib.pyplot as plt
import random

def load_file(filename: str):
    f = open(filename, 'r')
    graph = np.empty((0,3), int)
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
        length += distance_matrix[graph[x], graph[x-1]]
    return length

def change_of_length(first_vertex: int, second_vertex: int, new_vertex: int, distance_matrix: np.ndarray):
    return distance_matrix[first_vertex, new_vertex] + distance_matrix[second_vertex, new_vertex] - distance_matrix[first_vertex, second_vertex]


def create_greedy_cycles(distance_matrix: np.ndarray):
    first_cycle = np.array([0, 0])
    random_vertex = random.randint(1, distance_matrix.shape[0] - 1)
    second_cycle = np.array([random_vertex, random_vertex])
    free_vertices = np.arange(1, distance_matrix.shape[0] - 1, dtype = int)
    free_vertices = np.delete(free_vertices, np.where(free_vertices == random_vertex))
    first = True
    while np.any(free_vertices):
        best_value = -1
        index_graph = -1
        best_vertex = -1
        if first:
            for x in range(1, len(first_cycle)):
                for vertex in free_vertices:
                    if change_of_length(first_cycle[x-1], first_cycle[x], vertex, distance_matrix) < best_value or best_value == -1:
                        best_value = change_of_length(first_cycle[x-1], first_cycle[x], vertex, distance_matrix)
                        index_graph = x
                        best_vertex = vertex
            first_cycle = np.concatenate((first_cycle[:index_graph], [best_vertex], first_cycle[index_graph:])) #it runs faster than insert
            free_vertices = np.delete(free_vertices, np.where(free_vertices == best_vertex))
            first = not first
        else:
            for x in range(1, len(second_cycle)):
                for vertex in free_vertices:
                    if change_of_length(second_cycle[x-1], second_cycle[x], vertex, distance_matrix) < best_value or best_value == -1:
                        best_value = change_of_length(second_cycle[x-1], second_cycle[x], vertex, distance_matrix)
                        index_graph = x
                        best_vertex = vertex
            second_cycle = np.concatenate((second_cycle[:index_graph], [best_vertex], second_cycle[index_graph:])) #it runs faster than insert
            free_vertices = np.delete(free_vertices, np.where(free_vertices == best_vertex))
            first = not first
    return first_cycle, second_cycle

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
    
    plt.plot(x1, y1, 'bo', linestyle="--")
    plt.plot(x2, y2, 'o', linestyle="--", color="red")
    plt.title("Greedy cycle")
    plt.show()

graph = load_file("kroA100.tsp")
distance_matrix = create_distance_matrix(graph)
first, second = create_greedy_cycles(distance_matrix)
print(first, second)
print(check_length(first, distance_matrix), check_length(second, distance_matrix))
plot(first, second, graph)