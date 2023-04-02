#include <iostream>
#include <vector>
#include <math.h>
#include <list>
#include <map>

#include "read_data.cpp"
#include "regret_heuristic.cpp"
#include "local_search.cpp"


int main(){

    // wymiana krawędzi testy     
    std::vector<int> replec_edge =  edge_replacment({1,2,3,4,5,6,7,8,9}, 1, 5); // random statment are not lots to easy testing
    std::vector<int> correct = {1,2,6,5,4,3,7,8,9};
    assert(std::equal(replec_edge.begin(), replec_edge.end(), correct.begin()));

    std::vector<int> replec_edge_2 =  edge_replacment({1,2,3,4,5,6,7,8,9}, 0, 2); // random statment are not lots to easy testing
    std::vector<int> correct_2 = {1,3,2,4,5,6,7,8,9};
    assert(std::equal(replec_edge_2.begin(), replec_edge_2.end(), correct_2.begin()));

    std::vector<int> replec_edge_3 =  edge_replacment({1,2,3,4,5,6,7,8,9}, 6, 8); // random statment are not lots to easy testing
    std::vector<int> correct_3 = {1,2,3,4,5,6,7,9,8};
    assert(std::equal(replec_edge_3.begin(), replec_edge_3.end(), correct_3.begin()));

    //count_delta_function testy 
    // minimalizujemy
    //dla lepszej starej zwróci l.dodatnią
    // a dla lepszej nowej ujemną 
    int wynik =  count_delta_function({{0,3,1,6},{3,0,5,2},{1,5,0,4},{6,2,4,0}}, {0,1,2,3}, {0,3,2,1});
    assert(wynik == 0);


    std::vector<Node> nodes_corrdinats = read_data("kroA100.tsp");
    std::vector<std::vector<int>> distance_matrix = create_distance_matrix(nodes_corrdinats);
    std::pair cycles = create_two_tsp_cycles_regret_heurystic(distance_matrix, 0);
    std::cout<<"regret heuristic: length1 : "<<cycle_length(distance_matrix, cycles.first) <<" length2 : "<<cycle_length(distance_matrix, cycles.second)<<"\n"; 
    
    std::pair<std::vector<int>, std::vector<int>> greedy_paths = greedy_local_search_for_pair(cycles, distance_matrix);
    std::cout<<"greedy local search: length1 : "<<cycle_length(distance_matrix, std::list(greedy_paths.first.begin(), greedy_paths.first.end())) <<" length2 : "<<cycle_length(distance_matrix, std::list(greedy_paths.second.begin(), greedy_paths.second.end()))<<"\n"; 

    std::pair<std::vector<int>, std::vector<int>> steepeset_paths = steepest_local_search_for_pair(cycles, distance_matrix);
    std::cout<<"steeepsetlength1 : "<<cycle_length(distance_matrix, std::list(steepeset_paths.first.begin(), steepeset_paths.first.end())) <<" length2 : "<<cycle_length(distance_matrix, std::list(steepeset_paths.second.begin(), steepeset_paths.second.end()))<<"\n"; 

    return 0;
}
