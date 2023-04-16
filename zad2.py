import numpy as np
from main import *

def create_random_cycles(size_of_cycle: int)->tuple:
    first_cycle = np.random.choice(range(size_of_cycle), size = int(size_of_cycle/2), replace=False)
    sec = set(range(size_of_cycle)) - set(first_cycle)
    secend_cycle = np.random.choice(list(sec), size = int(size_of_cycle/2), replace=False)
    return first_cycle, secend_cycle


def count_delta_for_swap_edges(cycle: np.array, first_rand: int, second_rand: int, distance_matrix: np.array)->np.array:
    cycle = list(cycle)
    dist_without_change = sum([distance_matrix[i][j] for i,j in zip(cycle[first_rand:second_rand+1] , cycle[first_rand+1:second_rand+1])])
    # dist_without_change += distance_matrix[cycle[-1]][cycle[0]]
    cycle[first_rand+1:second_rand] = reversed(cycle[first_rand+1:second_rand])
    dist_with_change = sum([distance_matrix[i][j] for i,j in zip(cycle[first_rand:second_rand+1], cycle[first_rand+1:second_rand+1])])
    return dist_with_change - dist_without_change 


def change_edge(cycle: np.array, first_rand: int, second_rand)->np.array:
    cycle = list(cycle)
    cycle[first_rand+1:second_rand] = reversed(cycle[first_rand+1:second_rand])
    return np.array(cycle) 


def random_walk(starting_cycle: np.array, distance_matrix:np.array)->np.array:

    for _ in starting_cycle:
        first_rand = random.randint(0, (distance_matrix.shape[0]/2) - 2)
        secend_rand = random.randint(first_rand, distance_matrix.shape[0]/2)
        delta = count_delta_for_swap_edges(starting_cycle, first_rand, secend_rand, distance_matrix)
        if delta < 0:
            return change_edge(starting_cycle, first_rand, secend_rand)
        
    return starting_cycle


def random_walk_pair(starting_first_cycle: np.array, starting_secend_cycle: np.array, distance_matrix: np.array)->tuple:
    
    return random_walk(starting_first_cycle, distance_matrix), random_walk(starting_secend_cycle, distance_matrix)

if __name__ == "__main__":

    graph = load_file("kroA100.tsp")
    distance_matrix = create_distance_matrix(graph)

    first_random_cycle, secend_random_cycle = create_random_cycles(distance_matrix.shape[0])
    print("random", check_length(first_random_cycle, distance_matrix) + check_length(secend_random_cycle, distance_matrix))

    # first_nn, second_nn = create_greedy_cycles(distance_matrix)
    # print("greedy", check_length(first_nn, distance_matrix) + check_length(second_nn, distance_matrix))

    random_walk_pair_first, random_walk_pair_secend = random_walk_pair(first_random_cycle, secend_random_cycle, distance_matrix)
    print("random walk", check_length(random_walk_pair_first, distance_matrix) + check_length(random_walk_pair_secend, distance_matrix))

