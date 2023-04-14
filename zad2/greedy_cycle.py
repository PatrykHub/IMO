import random
from helpers import *


def append_cycle(
    cycle: np.ndarray, distance_matrix: np.ndarray, free_vertices: np.ndarray
):
    best_value = -1
    index_graph = -1
    best_vertex = -1
    for x in range(1, len(cycle)):
        for vertex in free_vertices:
            if (
                change_of_length(cycle[x - 1], cycle[x], vertex, distance_matrix)
                < best_value
                or best_value == -1
            ):
                best_value = change_of_length(
                    cycle[x - 1], cycle[x], vertex, distance_matrix
                )
                index_graph = x
                best_vertex = vertex
    cycle = np.concatenate(
        (cycle[:index_graph], [best_vertex], cycle[index_graph:])
    )  # it runs faster than insert
    free_vertices = np.delete(free_vertices, np.where(free_vertices == best_vertex))
    return cycle, free_vertices


def create_greedy_cycles(distance_matrix: np.ndarray):
    first_cycle = np.array([0, 0])
    random_vertex = random.randint(1, distance_matrix.shape[0] - 1)
    second_cycle = np.array([random_vertex, random_vertex])
    free_vertices = np.arange(1, distance_matrix.shape[0] - 1, dtype=int)
    free_vertices = np.delete(free_vertices, np.where(free_vertices == random_vertex))
    first = True
    while np.any(free_vertices):
        if first:
            first_cycle, free_vertices = append_cycle(
                first_cycle, distance_matrix, free_vertices
            )
            first = not first
        else:
            second_cycle, free_vertices = append_cycle(
                second_cycle, distance_matrix, free_vertices
            )
            first = not first
    return first_cycle, second_cycle
