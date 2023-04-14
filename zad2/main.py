from greedy_cycle import *
from helpers import *

def switch_vertices(cycle: np.ndarray, first_vertex: int, second_vertex: int)

graph = load_file("../kroA100.tsp")
distance_matrix = create_distance_matrix(graph)
first, second = create_greedy_cycles(distance_matrix)
print(first, second)
print(check_length(first, distance_matrix), check_length(second, distance_matrix))
plot(first, second, graph)