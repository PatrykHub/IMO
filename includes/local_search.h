#pragma once
#include <vector>
#include <list>
// #include "read_data.h"

std::vector<int> edge_replacment(std::vector<int> path, int random_start, int random_to);

int cycle_length(std::vector<std::vector<int>> distance_matrix, std::list<int> cycle);

int count_delta_function(std::vector<std::vector<int>> distance_matrix, std::vector<int> old_path, std::vector<int> new_path);

std::vector<int> greedy_local_search(std::vector<int> staring_path, std::vector<std::vector<int>> distance_matrix);

std::vector<int> best_from_all(std::vector<int> staring_path, std::vector<std::vector<int>> distance_matrix);

std::pair<std::vector<int>, std::vector<int>> greedy_local_search_for_pair(std::pair<std::list<int>, std::list<int>> staring_paths, std::vector<std::vector<int>> distance_matrix);

std::vector<int>steepest_local_search(std::vector<int> staring_path, std::vector<std::vector<int>> distance_matrix);

std::pair<std::vector<int>, std::vector<int>> steepest_local_search_for_pair(std::pair<std::list<int>, std::list<int>> staring_paths, std::vector<std::vector<int>> distance_matrix);

std::pair<std::vector<int>, std::vector<int>> generate_random_cycles(std::vector<std::vector<int>> distance_matrix);