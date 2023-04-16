import numpy as np
import matplotlib.pyplot as plt

def swap_vertices(
    first_cycle: np.ndarray,
    second_cycle: np.ndarray,
    first_vertex: int,
    second_vertex: int,
):
    """Function swaps first_vertex from first cycle with second_vertex from second_cycle

    :param first_cycle: Numpy array representing first cycle
    :param second_cycle: Numpy array representing second cycle
    :param first_vertex: Vertex that is being replaced from first cycle
    :param second_vertex: Vertex that is being replaced from second cycle
    :return: Two cycles with replaced wertices
    """
    (
        first_cycle[np.where(first_cycle == first_vertex)],
        second_cycle[np.where(second_cycle == second_vertex)],
    ) = (second_vertex, first_vertex)
    return first_cycle, second_cycle


def swap_edges(cycle: np.ndarray, first_vertex: int, second_vertex: int):
    """Function switches two edges in cyce. First edge begins in first_vertex and second edge begins in second_vertex.

    :param cycle: Numpy array representing cycle in which edges are being swapped
    :param first_vertex: Beginning of first edge
    :param second_vertex: Beginning of second edge
    :return: Numpy array representing cycle witch swapped edges
    """
    first_index = np.where(cycle == first_vertex)[0][0]
    second_index = np.where(cycle == second_vertex)[0][0]
    if first_index > second_index:
        second_index, first_index = first_index, second_index
    

    return np.concatenate(
        (
            cycle[: first_index + 1],
            cycle[second_index:first_index:-1],
            cycle[second_index + 1 :],
        )
    )



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


def plot(first_cycle: np.ndarray, second_cycle: np.ndarray, graph: np.ndarray, title):
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
    plt.title(title)
    plt.show()
