from greedy_cycle import *
from helpers import *


def switch_vertices(
    first_cycle: np.ndarray,
    second_cycle: np.ndarray,
    first_vertex: int,
    second_vertex: int,
):
    (
        first_cycle[np.where(first_cycle == first_vertex)],
        second_cycle[np.where(second_cycle == second_vertex)],
    ) = (second_vertex, first_vertex)
    return first_cycle, second_cycle


def switch_edges(cycle: np.ndarray, first_vertex: int, second_vertex: int):
    first_index = np.where(cycle == first_vertex)[0][0]

    if second_vertex == cycle[-1]:
        second_index, first_index = first_index, 0
    else:
        second_index = np.where(cycle == second_vertex)[0][0]

    return np.concatenate(
        (
            cycle[: first_index + 1],
            cycle[second_index:first_index:-1],
            cycle[second_index + 1 :],
        )
    )


def calculate_swap_of_verticec_cost(
    first_cycle: np.ndarray,
    second_cycle: np.ndarray,
    first_vertex: int,
    second_vertex: int,
    distance_matrix: np.ndarray,
):
    first_index = np.where(first_cycle == first_vertex)[0]
    first_previous = first_cycle[first_index[-1] - 1]
    first_next = first_cycle[first_index[0] + 1]

    second_index = np.where(second_cycle == second_vertex)[0]
    second_previous = second_cycle[second_index[-1] - 1]
    second_next = second_cycle[second_index[0] + 1]
    cost = (
        distance_matrix[first_previous, second_vertex]
        + distance_matrix[first_next, second_vertex]
        + distance_matrix[second_previous, first_vertex]
        + distance_matrix[second_next, first_vertex]
        - distance_matrix[second_previous, second_vertex]
        - distance_matrix[second_next, second_vertex]
        - distance_matrix[first_previous, first_vertex]
        - distance_matrix[first_next, first_vertex]
    )
    return cost


def create_vertices_cost_matrix(
    first_cycle: np.ndarray, second_cycle: np.ndarray, distance_matrix: np.ndarray
):
    vertices_cost = np.ones_like(distance_matrix)
    for x, y in np.ndindex(vertices_cost.shape):
        if x >= y:
            continue
        if x in first_cycle and y in second_cycle:
            vertices_cost[x, y] = calculate_swap_of_verticec_cost(
                first_cycle, second_cycle, x, y, distance_matrix
            )
        elif y in first_cycle and x in second_cycle:
            vertices_cost[x, y] = calculate_swap_of_verticec_cost(
                first_cycle, second_cycle, y, x, distance_matrix
            )
    return vertices_cost


def update_vertices_cost_matrix(
    vertex: int,
    first_cycle: np.ndarray,
    second_cycle: np.ndarray,
    vertices_cost: np.ndarray,
    distance_matrix: np.ndarray,
):
    for x in range(vertices_cost.shape[0]):
        if x == vertex:
            continue
        if x in first_cycle:
            vertices_cost[vertex, x] = 1
            vertices_cost[x, vertex] = 1
            continue
        if x > vertex:
            vertices_cost[vertex, x] = calculate_swap_of_verticec_cost(
                first_cycle, second_cycle, vertex, x, distance_matrix
            )
        vertices_cost[x, vertex] = calculate_swap_of_verticec_cost(
            first_cycle, second_cycle, vertex, x, distance_matrix
        )
    return vertices_cost


def steepest_vertices(
    first_cycle: np.ndarray,
    second_cycle: np.ndarray,
    vertices_cost: np.ndarray,
    distance_matrix,
):
    while True:
        indices = divmod(vertices_cost.argmin(), vertices_cost.shape[1])
        if vertices_cost[indices[0], indices[1]] >= 0:
            break
        else:
            if indices[0] in first_cycle:
                first_cycle, second_cycle = switch_vertices(
                    first_cycle, second_cycle, indices[0], indices[1]
                )
                vertices_cost = update_vertices_cost_matrix(
                    indices[0],
                    second_cycle,
                    first_cycle,
                    vertices_cost,
                    distance_matrix,
                )
                vertices_cost = update_vertices_cost_matrix(
                    indices[1],
                    first_cycle,
                    second_cycle,
                    vertices_cost,
                    distance_matrix,
                )
            else:
                first_cycle, second_cycle = switch_vertices(
                    first_cycle, second_cycle, indices[1], indices[0]
                )
                vertices_cost = update_vertices_cost_matrix(
                    indices[1],
                    second_cycle,
                    first_cycle,
                    vertices_cost,
                    distance_matrix,
                )
                vertices_cost = update_vertices_cost_matrix(
                    indices[0],
                    first_cycle,
                    second_cycle,
                    vertices_cost,
                    distance_matrix,
                )
    return first, second


graph = load_file("kroA100.tsp")
distance_matrix = create_distance_matrix(graph)
first, second = create_greedy_cycles(distance_matrix)
print(first, second)
vertices_cost = create_vertices_cost_matrix(first, second, distance_matrix)
print(check_length(first, distance_matrix), check_length(second, distance_matrix))
first, second = steepest_vertices(first, second, vertices_cost, distance_matrix)
print(check_length(first, distance_matrix), check_length(second, distance_matrix))
plot(first, second, graph)
