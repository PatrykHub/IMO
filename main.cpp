#include <iostream>
#include <vector>
#include <math.h>
#include <list>
#include <map>

#include "read_data.cpp"
#include "regret_heuristic.cpp"
#include "local_search.cpp"


int main(){

    std::vector<Node> nodes_corrdinats = read_data("kroA100.tsp");
    
    std::vector<std::vector<int>> distance_matrix = create_distance_matrix(nodes_corrdinats);
    
    std::pair cycles = create_two_tsp_cycles_regret_heurystic(distance_matrix, 0);

    // std::cout<<"length1 : "<<cycle_length(distance_matrix, c.first) <<" length2 : "<<cycle_length(distance_matrix, c.second)<<"\n"; 

    // for (auto i: cycles.first){
    //     std::cout << i << " ";
    // }  
    // std::cout << std::endl; 

    // wymiana krawędzi testy 
    std::list<int> replec_edge =  edge_replacment({1,2,3,4,5,6,7,8,9}, 1, 5); // random statment are not lots to easy testing
    std::list<int> correct = {1,2,6,5,4,3,7,8,9};
    assert(std::equal(replec_edge.begin(), replec_edge.end(), correct.begin()));

    std::list<int> replec_edge_2 =  edge_replacment({1,2,3,4,5,6,7,8,9}, 0, 2); // random statment are not lots to easy testing
    std::list<int> correct_2 = {1,3,2,4,5,6,7,8,9};
    assert(std::equal(replec_edge_2.begin(), replec_edge_2.end(), correct_2.begin()));

    std::list<int> replec_edge_3 =  edge_replacment({1,2,3,4,5,6,7,8,9}, 6, 8); // random statment are not lots to easy testing
    std::list<int> correct_3 = {1,2,3,4,5,6,7,9,8};
    assert(std::equal(replec_edge_3.begin(), replec_edge_3.end(), correct_3.begin()));

    return 0;
}
