from greedy_cycle import *
from helpers import *


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


def calculate_swap_of_edges_cost(
    first_edge_beginning: int,
    first_edge_end: int,
    second_edge_beginning: int,
    second_edge_end: int,
    distance_matrix: np.ndarray,
):
    """Calculates cost of swapping edges in cycle using distance matrix

    :param first_edge_beginning: Beginnig of first edge
    :param first_edge_end: Ending of first edge
    :param second_edge_beginning: Beginnig of second edge
    :param second_edge_end: Ending of second edge
    :param distance_matrix: Matrix containing euclidean distances between points
    :return: Cost of swapping edges in cycle
    """
    return (
        distance_matrix[first_edge_beginning, second_edge_beginning]
        + distance_matrix[first_edge_end, second_edge_end]
        - distance_matrix[first_edge_beginning, first_edge_end]
        - distance_matrix[second_edge_beginning, second_edge_end]
    )


def create_edges_cost_matrix(
    first_cycle: np.ndarray, second_cycle: np.ndarray, distance_matrix: np.ndarray
):
    """Creates complete matrix filed with costs of swaping two edges.
    Row index points to vertex that begins first edge and column index points to vertex beginning second edge.
    Matrix is filled only in half to speed up calculation time.
    Furthermore rest if it and edges that cannot be replaced are filled with '1'.

    :param first_cycle: Numpy array representing first cycle
    :param second_cycle:Numpy array representing second cycle
    :param distance_matrix: Matrix containing euclidean distances between points
    :return: Matrix filed with costs of swaping two edges,
    """
    edges_cost = np.ones_like(distance_matrix)
    for x in range(first_cycle.shape[0] - 2):
        for y in range(x + 1, first_cycle.shape[0] - 1):
            if first_cycle[y] < first_cycle[x]:
                edges_cost[
                    first_cycle[y], first_cycle[x]
                ] = calculate_swap_of_edges_cost(
                    first_cycle[y],
                    first_cycle[y + 1],
                    first_cycle[x],
                    first_cycle[x + 1],
                    distance_matrix,
                )
            else:
                edges_cost[
                    first_cycle[x], first_cycle[y]
                ] = calculate_swap_of_edges_cost(
                    first_cycle[y],
                    first_cycle[y + 1],
                    first_cycle[x],
                    first_cycle[x + 1],
                    distance_matrix,
                )

    for y in range(second_cycle.shape[0] - 2):
        for x in range(x + 1, second_cycle.shape[0] - 1):
            if second_cycle[y] < second_cycle[x]:
                edges_cost[
                    second_cycle[y], second_cycle[x]
                ] = calculate_swap_of_edges_cost(
                    second_cycle[y],
                    second_cycle[y + 1],
                    second_cycle[x],
                    second_cycle[x + 1],
                    distance_matrix,
                )
            else:
                edges_cost[
                    second_cycle[x], second_cycle[y]
                ] = calculate_swap_of_edges_cost(
                    second_cycle[y],
                    second_cycle[y + 1],
                    second_cycle[x],
                    second_cycle[x + 1],
                    distance_matrix,
                )
    return edges_cost


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
    distance_matrix: np.ndarray,
):
    while True:
        indices = divmod(vertices_cost.argmin(), vertices_cost.shape[1])
        if vertices_cost[indices[0], indices[1]] >= 0:
            break
        else:
            if indices[0] in first_cycle:
                first_cycle, second_cycle = swap_vertices(
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
                first_cycle, second_cycle = swap_vertices(
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


def steepest_edges(
    first_cycle: np.ndarray,
    second_cycle: np.ndarray,
    vertices_cost: np.ndarray,
    edges_cost: np.ndarray,
    distance_matrix: np.ndarray,
):
    while True:
        indices_vertices = divmod(vertices_cost.argmin(), vertices_cost.shape[1])
        indices_edges = divmod(edges_cost.argmin(), edges_cost.shape[1])
        if (
            vertices_cost[indices_vertices[0], indices_vertices[1]] >= 0
            and edges_cost[indices_edges[0], indices_edges[1]] >= 0
        ):
            break
        elif (
            vertices_cost[indices_vertices[0], indices_vertices[1]]
            < edges_cost[indices_edges[0], indices_edges[1]]
        ):
            if indices_vertices[0] in first_cycle:
                first_cycle, second_cycle = swap_vertices(
                    first_cycle, second_cycle, indices_vertices[0], indices_vertices[1]
                )
                vertices_cost = update_vertices_cost_matrix(
                    indices_vertices[0],
                    second_cycle,
                    first_cycle,
                    vertices_cost,
                    distance_matrix,
                )
                vertices_cost = update_vertices_cost_matrix(
                    indices_vertices[1],
                    first_cycle,
                    second_cycle,
                    vertices_cost,
                    distance_matrix,
                )
            else:
                first_cycle, second_cycle = swap_vertices(
                    first_cycle, second_cycle, indices_vertices[1], indices_vertices[0]
                )
                vertices_cost = update_vertices_cost_matrix(
                    indices_vertices[1],
                    second_cycle,
                    first_cycle,
                    vertices_cost,
                    distance_matrix,
                )
                vertices_cost = update_vertices_cost_matrix(
                    indices_vertices[0],
                    first_cycle,
                    second_cycle,
                    vertices_cost,
                    distance_matrix,
                )
        else:
            if indices_edges[0] in first_cycle:
                first_cycle = swap_edges(
                    first_cycle, indices_edges[0], indices_edges[1]
                )
            elif indices_edges[0] in second_cycle:
                second_cycle = swap_edges(
                    second_cycle, indices_edges[0], indices_edges[1]
                )
        edges_cost = create_edges_cost_matrix(
            first_cycle, second_cycle, distance_matrix
        )
    return first, second


graph = load_file("kroA100.tsp")
distance_matrix = create_distance_matrix(graph)
first, second = create_greedy_cycles(distance_matrix)
print(first, second)
edges_cost = create_edges_cost_matrix(first, second, distance_matrix)
np.savetxt("test2.txt", edges_cost)
vertices_cost = create_vertices_cost_matrix(first, second, distance_matrix)
print(check_length(first, distance_matrix), check_length(second, distance_matrix))
first, second = steepest_edges(
    first, second, vertices_cost, edges_cost, distance_matrix
)
print(check_length(first, distance_matrix), check_length(second, distance_matrix))
plot(first, second, graph)
