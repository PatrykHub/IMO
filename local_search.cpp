#include <iostream>
#include <vector>
#include <math.h>
#include <list>
#include <map>

std::list<int> edge_replacment(std::vector<int> path, int random_start, int random_to){ // random statment are not lots to easy testing
    // std::list path = std::list(path.begin(), path.end());
    std::list<int> path_with_replec_edge;

    std::list<int> first_slice = std::list<int>(path.begin(), path.begin()+random_start + 1);
    path_with_replec_edge.insert(path_with_replec_edge.end(), first_slice.begin(), first_slice.end());

    std::list<int> secend_slice = std::list<int>(path.begin()+random_start + 1, path.begin()+random_to+1);
    secend_slice.reverse();
    path_with_replec_edge.insert(path_with_replec_edge.end(), secend_slice.begin(), secend_slice.end());

    std::list<int> third_slice = std::list<int>(path.begin()+random_to+1, path.end());
    path_with_replec_edge.insert(path_with_replec_edge.end(), third_slice.begin(), third_slice.end());

    return path_with_replec_edge;
}


int cycle_length(std::vector<std::vector<int>> distance_matrix, std::list<int> cycle){
    int prev = -1;
    int length = 0;
    for(auto it = cycle.begin(); it != cycle.end(); ++it){
        if(prev != -1){
            length += distance_matrix[prev][*it];
        }
        prev = *it;
    }
    return length;
}

int count_delta_function(std::vector<std::vector<int>> distance_matrix, std::vector<int> old_path, std::vector<int> new_path){
   std::list old_path_l = std::list(old_path.begin(), old_path.end());
   std::list new_path_l = std::list(new_path.begin(), new_path.end());

   return cycle_length(distance_matrix, new_path_l) -  cycle_length(distance_matrix, old_path_l);
}