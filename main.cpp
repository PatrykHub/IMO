#include <iostream>
#include <vector>
#include <math.h>
#include <algorithm>
#include <numeric>
#include <list>
#include <map>

#include "read_data.cpp"


int count_euclidean_distance(Node node_1, Node node_2){
    return round(sqrt(pow(node_1.x - node_2.x, 2) + pow(node_1.y - node_2.y, 2)));
}

std::vector<std::vector<int>> create_distance_matrix(std::vector<Node> nodes_corrdinats){
    
    std::vector<std::vector<int>> distance_matrix ; // TODO wielkość 

    for (int i=0; i<nodes_corrdinats.size() ; i++){
        std::vector<int> row_of_distance_matrix;
        for (int j=0; j<nodes_corrdinats.size() ; j++){
            int distance = count_euclidean_distance(nodes_corrdinats[i], nodes_corrdinats[j]);
            row_of_distance_matrix.push_back(distance);
        }
        distance_matrix.push_back(row_of_distance_matrix);
    }

    return distance_matrix;
}

int find_min_index_without_list(std::vector<int> row_of_distance_matrix, std::list<int> indexies_without){


    std::list<int> row_of_distance_matrix_list(row_of_distance_matrix.begin(), row_of_distance_matrix.end());
    
    for (int to_remove: indexies_without){
        auto iterator_to_remove = row_of_distance_matrix_list.begin();
        std::advance(iterator_to_remove, to_remove);
        row_of_distance_matrix_list.erase(iterator_to_remove);
    }
    
    auto min_element_from_uncoplate_list = std::min_element(row_of_distance_matrix_list.begin(), row_of_distance_matrix_list.end());
    

    std::cout << "Najmniejszy element na liście to: " << *min_element_from_uncoplate_list << std::endl;

    int szukany = *min_element_from_uncoplate_list;
    
    auto it = std::find(row_of_distance_matrix.begin(), row_of_distance_matrix.end(), szukany);
    
    if (it != row_of_distance_matrix.end()) {
        int indeks = std::distance(row_of_distance_matrix.begin(), it);
        std::cout << "Element " << szukany << " znajduje się na indeksie " << indeks << std::endl;
        return indeks;
    }

    else {
        std::cout << "Element " << szukany << " nie został znaleziony w wektorze." << std::endl;
        return -1;
    }
}

std::pair<std::list<int>, std::list<int>> create_two_tsp_cycles(std::vector<std::vector<int>> distance_matrix){
    
    std::list <int> first_cycle, secend_cycle;

    std::list<int> free_nodes(distance_matrix[0].size()) ; // vector with 100 ints.
    std::iota (std::begin(free_nodes), std::end(free_nodes), 0); // Fill with 0, 1, ..., 99.

    
    //starting first cycle from 0 node
    int init_node_firs_cycle = 0;
    free_nodes.remove(init_node_firs_cycle);
    first_cycle.push_back(init_node_firs_cycle);

    //starting secend cycle from node most faraway from 0 node 
    auto max_pos = std::max_element(distance_matrix[init_node_firs_cycle].begin(), distance_matrix[init_node_firs_cycle].end());
    int init_node_secend_cycle = std::distance(distance_matrix[init_node_firs_cycle].begin(), max_pos);
    free_nodes.remove(init_node_secend_cycle);
    secend_cycle.push_back(init_node_secend_cycle);
    
    int k=0;
    while (first_cycle.size()+secend_cycle.size() < distance_matrix[0].size()){
        if (k%2 == 0){//ferst cicle
            std::map<int, int> index_min_candidate ; 

            int ferst_element = first_cycle.front();
            

            for (auto it = std::next(first_cycle.begin()); it != std::prev(first_cycle.end()); ++it) {
                std::cout << *it << " ";
            }

            k++;
        }
        else{//secend cicle 


            k++;
        }
    }

    return std::pair(first_cycle, secend_cycle);

}

int main(){

    std::vector<Node> nodes_corrdinats = read_data("example.txt");
    
    for (auto i: nodes_corrdinats){
        std::cout << i.id <<" "<< i.x <<" "<< i.y << std::endl;
    }

    std::cout << count_euclidean_distance(nodes_corrdinats[0], nodes_corrdinats[0]) << std::endl; 

    std::vector<std::vector<int>> distance_matrix = create_distance_matrix(nodes_corrdinats);

    for (auto i: distance_matrix){
        for (auto j: i){
            std::cout << j << " ";
        }
        std::cout<< std::endl;
    }

    // create_two_tsp_cycles(distance_matrix);

    std::cout << find_min_index_without_list({4,0,1,8,3}, {1,3}) << std::endl;
    std::cout << find_min_index_without_list({4,0,1,8,3}, {}) << std::endl;
    std::cout << find_min_index_without_list({}, {}) << std::endl;


    return 0;
}
