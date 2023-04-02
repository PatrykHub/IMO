#pragma once
#include <vector>
#include <list>

int find_min_index_with_included_indexes(std::vector<int> vec, std::list<int> included_indexes);

std::pair<std::list<int>, std::list<int>> create_two_tsp_cycles_regret_heurystic(std::vector<std::vector<int>> distance_matrix, int starting_index);

