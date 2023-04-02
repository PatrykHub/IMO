#include <iostream>
#include <vector>
#include <math.h>
#include <list>
#include <map>
#include <random>
#include <utility>
#include "../includes/local_search.h"

std::vector<int> edge_replacment(std::vector<int> path, int random_start, int random_to){ // random statment are not lots to easy testing
    // std::list path = std::list(path.begin(), path.end());
    std::list<int> path_with_replec_edge;

    std::list<int> first_slice = std::list<int>(path.begin(), path.begin()+random_start + 1);
    path_with_replec_edge.insert(path_with_replec_edge.end(), first_slice.begin(), first_slice.end());

    std::list<int> secend_slice = std::list<int>(path.begin()+random_start + 1, path.begin()+random_to+1);
    secend_slice.reverse();
    path_with_replec_edge.insert(path_with_replec_edge.end(), secend_slice.begin(), secend_slice.end());

    std::list<int> third_slice = std::list<int>(path.begin()+random_to+1, path.end());
    path_with_replec_edge.insert(path_with_replec_edge.end(), third_slice.begin(), third_slice.end());

    return std::vector(path_with_replec_edge.begin(), path_with_replec_edge.end());
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
    auto it = cycle.begin();
    return length += distance_matrix[prev][*it];
}

int count_delta_function(std::vector<std::vector<int>> distance_matrix, std::vector<int> old_path, std::vector<int> new_path){
   std::list old_path_l = std::list(old_path.begin(), old_path.end());
   std::list new_path_l = std::list(new_path.begin(), new_path.end());

   return cycle_length(distance_matrix, new_path_l) -  cycle_length(distance_matrix, old_path_l);
}


std::vector<int> greedy_local_search(std::vector<int> staring_path, std::vector<std::vector<int>> distance_matrix){

    std::vector<int> best_path = staring_path;

    while (true){
    // for random start od 0 do długosci 
    //     for random to od random start+1 do dlugosci 
        int random_start = rand() % staring_path.size();
        int random_to = rand()%(staring_path.size()-random_start + 1) + random_start;
        std::vector<int> propose_path = edge_replacment(best_path, random_start-1, random_to-1);
        if (count_delta_function(distance_matrix, best_path, propose_path) < 0){
            return propose_path;
        }
    }
}

std::pair<std::vector<int>, std::vector<int>> greedy_local_search_for_pair(std::pair<std::list<int>, std::list<int>> staring_paths, std::vector<std::vector<int>> distance_matrix){

    return std::pair(greedy_local_search(std::vector(staring_paths.first.begin(), staring_paths.first.end()), distance_matrix), greedy_local_search(std::vector(staring_paths.second.begin(), staring_paths.second.end()), distance_matrix));

}


std::vector<int>steepest_local_search(std::vector<int> staring_path, std::vector<std::vector<int>> distance_matrix){

    std::vector<int> best_path = staring_path;
    int i = 500; // do puki jest poprawa, dla każdeg owierzchołka licze delte i wybieram najelpepsze i aplikuje jeśli delta jest dodatnia a jak nie to stopuje o koniec 
    while (i>0){
        i--;
        std::vector<int> propose_path = greedy_local_search(staring_path, distance_matrix);
        if (count_delta_function(distance_matrix, best_path, propose_path) < 0){
            best_path = propose_path;
        }
    }
    return best_path;
}


std::pair<std::vector<int>, std::vector<int>> steepest_local_search_for_pair(std::pair<std::list<int>, std::list<int>> staring_paths, std::vector<std::vector<int>> distance_matrix){
    return std::pair(steepest_local_search(std::vector(staring_paths.first.begin(), staring_paths.first.end()), distance_matrix), steepest_local_search(std::vector(staring_paths.second.begin(), staring_paths.second.end()), distance_matrix));

}