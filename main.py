from neighbours import *
from collections import Counter

graph = load_file("kroA100.tsp")
distance_matrix = create_distance_matrix(graph)
#first, second = create_greedy_cycles(distance_matrix)
first, second = random_cycles(distance_matrix)
print(first, second)

#print(first)
#print("-----------------------------------")
#first = swap_edges(first, first[3], first[24])
#print([item for item, count in Counter(first).items() if count > 1])
#
#first = swap_edges(first, first[0], first[3])
#print([item for item, count in Counter(first).items() if count > 1])
#
#first = swap_edges(first, first[15], first[3])
#print([item for item, count in Counter(first).items() if count > 1])
#
#first = swap_edges(first, first[23], first[33])
#print([item for item, count in Counter(first).items() if count > 1])
#
#first = swap_edges(first, first[3], first[8])
#print([item for item, count in Counter(first).items() if count > 1])
#
#first = swap_edges(first, first[32], first[2])
#print([item for item, count in Counter(first).items() if count > 1])
#print("-----------------------------------")
#
#np.savetxt("test2.txt", edges_cost)
#np.savetxt("distance_matrix.txt", distance_matrix)

vertices_cost = create_vertices_cost_matrix(first, second, distance_matrix)
edges_cost = create_edges_cost_matrix(first, second, distance_matrix)

#print(check_length(first, distance_matrix), check_length(second, distance_matrix))


first1, second1 = steepest_vertices(np.copy(first), np.copy(second), vertices_cost, distance_matrix)

first2, second2 = steepest_edges(np.copy(first), np.copy(second), vertices_cost, edges_cost, distance_matrix)
print("-------------------")
print(check_length(first, distance_matrix), check_length(second, distance_matrix))
print(check_length(first1, distance_matrix), check_length(second1, distance_matrix))
print(check_length(first2, distance_matrix), check_length(second2, distance_matrix))

plot(first, second, graph, "Random")
plot(first1, second1, graph, "Steepest_vertices")
plot(first2, second2, graph, "Steepest_edges")
