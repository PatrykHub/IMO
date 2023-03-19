#include <iostream>
#include <vector>
#include <math.h>
#include <algorithm>
#include <numeric>
#include <list>
#include <map>
#include <bits/stdc++.h>

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
    

    //std::cout << "Najmniejszy element na liście to: " << *min_element_from_uncoplate_list << std::endl;

    int szukany = *min_element_from_uncoplate_list;
    
    auto it = std::find(row_of_distance_matrix.begin(), row_of_distance_matrix.end(), szukany);
    
    if (it != row_of_distance_matrix.end()) {
        int indeks = std::distance(row_of_distance_matrix.begin(), it);
        //td::cout << "Element " << szukany << " znajduje się na indeksie " << indeks << std::endl;
        return indeks;
    }

    else {
        //std::cout << "Element " << szukany << " nie został znaleziony w wektorze." << std::endl;
        return -1;
    }
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

std::pair<std::list<int>, std::list<int>> create_two_tsp_cycles(std::vector<std::vector<int>> distance_matrix){
    
    std::list <int> first_cycle, second_cycle, banned;

    std::list<int> free_nodes(distance_matrix[0].size()) ; // vector with 100 ints.
    std::iota (std::begin(free_nodes), std::end(free_nodes), 0); // Fill with 0, 1, ..., 99.

    
    //starting first cycle from 0 node
    int init_node_first_cycle = 0;
    free_nodes.remove(init_node_first_cycle);
    first_cycle.push_back(init_node_first_cycle);
    banned.push_back(init_node_first_cycle);

    //starting secend cycle from node most faraway from 0 node 
    auto max_pos = std::max_element(distance_matrix[init_node_first_cycle].begin(), distance_matrix[init_node_first_cycle].end());
    int init_node_second_cycle = std::distance(distance_matrix[init_node_first_cycle].begin(), max_pos);
    free_nodes.remove(init_node_second_cycle);
    second_cycle.push_back(init_node_second_cycle);
    banned.push_back(init_node_second_cycle);

    //create cycles with two elements
    int next_index = find_min_index_without_list(distance_matrix[init_node_first_cycle], banned);
    free_nodes.remove(next_index);
    first_cycle.push_back(next_index);
    banned.push_back(next_index);

    next_index = find_min_index_without_list(distance_matrix[init_node_second_cycle], banned);
    free_nodes.remove(next_index);
    second_cycle.push_back(next_index);

    int curr_length;
    int place;
    int best_length;
    int k=0;
    int iterator = -1;
    while (free_nodes.size() != 0){
        next_index = -1;
        best_length = -1;
        if (k%2 == 0){//first cycle
            for (auto it = first_cycle.begin(); it != first_cycle.end(); ++it) {
                iterator += 1;
                for (auto el = free_nodes.begin(); el != free_nodes.end(); ++el) {
                    std::list<int> cycle = first_cycle;
                    std::list<int>::iterator it_c = cycle.begin();
                    std::advance(it_c, iterator);
                    cycle.insert(it_c, *el);
                    curr_length = cycle_length(distance_matrix, first_cycle);
                    if(curr_length < best_length || best_length == -1){
                        best_length = curr_length;
                        next_index = *el;
                        place = iterator;
                    }
                }
            }
            iterator = -1;
            free_nodes.remove(next_index);
            std::list<int>::iterator it_c = first_cycle.begin();
            std::advance(it_c, place);
            first_cycle.insert(it_c, next_index);

            k++;
        }
        else{//second cycle 
            for (auto it = second_cycle.begin(); it != second_cycle.end(); ++it) {
                iterator += 1;
                for (auto el = free_nodes.begin(); el != free_nodes.end(); ++el) {
                    std::list<int> cycle = second_cycle;
                    std::list<int>::iterator it_c = cycle.begin();
                    std::advance(it_c, iterator);
                    cycle.insert(it_c, *el);
                    curr_length = cycle_length(distance_matrix, cycle);
                    if(curr_length < best_length || best_length == -1){
                        best_length = curr_length;
                        next_index = *el;
                        place = iterator;
                    }
                }
            }
            iterator = -1;
            free_nodes.remove(next_index);
            std::list<int>::iterator it_c = second_cycle.begin();
            std::advance(it_c, place);
            second_cycle.insert(it_c, next_index);
            k++;
        }
    }
    first_cycle.push_back(*first_cycle.begin());
    second_cycle.push_back(*second_cycle.begin());
    return std::pair(first_cycle, second_cycle);

}

std::pair<std::list<int>, std::list<int>> create_two_tsp_cycles_greedy_cycle(std::vector<std::vector<int>> distance_matrix){
    
    std::list <int> first_cycle, second_cycle, banned;

    std::list<int> free_nodes(distance_matrix[0].size()) ; // vector with 100 ints.
    std::iota (std::begin(free_nodes), std::end(free_nodes), 0); // Fill with 0, 1, ..., 99.

    
    //starting first cycle from 0 node
    int init_node_first_cycle = 0;
    free_nodes.remove(init_node_first_cycle);
    first_cycle.push_back(init_node_first_cycle);
    banned.push_back(init_node_first_cycle);

    //starting secend cycle from node most faraway from 0 node 
    auto max_pos = std::max_element(distance_matrix[init_node_first_cycle].begin(), distance_matrix[init_node_first_cycle].end());
    int init_node_second_cycle = std::distance(distance_matrix[init_node_first_cycle].begin(), max_pos);
    free_nodes.remove(init_node_second_cycle);
    second_cycle.push_back(init_node_second_cycle);
    banned.push_back(init_node_second_cycle);

    //create cycles with two elements
    int next_index = find_min_index_without_list(distance_matrix[init_node_first_cycle], banned);
    free_nodes.remove(next_index);
    first_cycle.push_back(next_index);
    banned.push_back(next_index);
    first_cycle.push_back(init_node_first_cycle);

    next_index = find_min_index_without_list(distance_matrix[init_node_second_cycle], banned);
    free_nodes.remove(next_index);
    second_cycle.push_back(next_index);
    second_cycle.push_back(init_node_second_cycle);

    int curr_length;
    int place;
    int best_length;
    int k=0;
    int iterator = 0;
    while (free_nodes.size() != 0){
        next_index = -1;
        best_length = -1;
        if (k%2 == 0){//first cycle
            for (auto it = std::next(first_cycle.begin()); it != std::prev(first_cycle.end()); ++it) {
                iterator += 1;
                for (auto el = free_nodes.begin(); el != free_nodes.end(); ++el) {
                    std::list<int> cycle = first_cycle;
                    std::list<int>::iterator it_c = cycle.begin();
                    std::advance(it_c, iterator);
                    cycle.insert(it_c, *el);
                    curr_length = cycle_length(distance_matrix, first_cycle);
                    if(curr_length < best_length || best_length == -1){
                        best_length = curr_length;
                        next_index = *el;
                        place = iterator;
                    }
                }
            }
            iterator = 0;
            free_nodes.remove(next_index);
            std::list<int>::iterator it_c = first_cycle.begin();
            std::advance(it_c, place);
            first_cycle.insert(it_c, next_index);

            k++;
        }
        else{//second cycle 
            for (auto it = std::next(second_cycle.begin()); it != std::prev(second_cycle.end()); ++it) {
                iterator += 1;
                for (auto el = free_nodes.begin(); el != free_nodes.end(); ++el) {
                    std::list<int> cycle = second_cycle;
                    std::list<int>::iterator it_c = cycle.begin();
                    std::advance(it_c, iterator);
                    cycle.insert(it_c, *el);
                    curr_length = cycle_length(distance_matrix, cycle);
                    if(curr_length < best_length || best_length == -1){
                        best_length = curr_length;
                        next_index = *el;
                        place = iterator;
                    }
                }
            }
            iterator = 0;
            free_nodes.remove(next_index);
            std::list<int>::iterator it_c = second_cycle.begin();
            std::advance(it_c, place);
            second_cycle.insert(it_c, next_index);
            k++;
        }
    }

    return std::pair(first_cycle, second_cycle);

}


int find_min_with_included_indexes(std::vector<int> vec, std::list<int> included_indexes){

    int min_value = INT_MAX;  // minimalna wartość początkowa
    int min_inex;

    for (int i : included_indexes) {
        if (i >= 0 && i < vec.size()) {  // jeśli indeks jest poprawny
            if (vec[i] < min_value) {
                min_value = vec[i];
                min_inex = i;
            }
        }
    }

    return min_inex;
}
std::pair<std::list<int>, std::list<int>> create_two_tsp_cycles_regret_heurystic(std::vector<std::vector<int>> distance_matrix){ 
    

    std::list <int> first_cycle, second_cycle, banned;
    std::list<int> free_nodes(distance_matrix[0].size());
    
    std::iota(free_nodes.begin(), free_nodes.end(), 0);

    int init_node_ferst_cycle = 0; // you cen make it random 
    free_nodes.remove(init_node_ferst_cycle);
    first_cycle.push_back(init_node_ferst_cycle);
    int secend_node_ferst_cycle = find_min_with_included_indexes(distance_matrix[init_node_ferst_cycle], free_nodes); // STL containers.
    free_nodes.remove(secend_node_ferst_cycle);
    first_cycle.push_back(secend_node_ferst_cycle);

    int init_node_secend_cycle = std::distance(distance_matrix[init_node_ferst_cycle].begin(),std::max_element(distance_matrix[init_node_ferst_cycle].begin(), distance_matrix[init_node_ferst_cycle].end()));
    free_nodes.remove(init_node_secend_cycle);
    second_cycle.push_back(init_node_secend_cycle);
    int secend_node_secend_cycle = find_min_with_included_indexes(distance_matrix[init_node_secend_cycle], free_nodes); // STL containers.
    free_nodes.remove(secend_node_secend_cycle);
    second_cycle.push_back(secend_node_secend_cycle);


    int i = 1;
    while (!free_nodes.empty()){
        i++;
        if(i%2==0){
            std::list<int>::iterator v1, v2;
            int v_new;
            float cost;
            float best_cost;
            float second_best_cost;
            float regret;
            float highest_regret = 0;
            std::pair<int, std::list<int>::iterator> best_vertices; // new, second
            std::list<int>::iterator best_position_for_vertex; // index of the element before which we should insert

            for (int v_new: free_nodes)
            {
                best_cost = std::numeric_limits<int>::max();

                for (auto it = first_cycle.begin(); it != first_cycle.end(); it++)
                {
                    v1 = it;
                    v2 = std::next(it) != first_cycle.end() ? std::next(it) : first_cycle.begin();

                    cost = distance_matrix[*v1][v_new] + distance_matrix[v_new][*v2] - distance_matrix[*v1][*v2];

                    if (cost < best_cost){
                        second_best_cost = best_cost;
                        best_cost = cost;
                        best_position_for_vertex = v2;
                    }
                }
                regret = second_best_cost - best_cost;
                if (regret > highest_regret)
                {
                    highest_regret = regret;
                    best_vertices = {v_new, best_position_for_vertex};
                }
            }
            first_cycle.insert(best_vertices.second, best_vertices.first);
            free_nodes.remove(best_vertices.first);

        }
        else{
                        std::list<int>::iterator v1, v2;
            int v_new;
            float cost;
            float best_cost;
            float second_best_cost;
            float regret;
            float highest_regret = 0;
            std::pair<int, std::list<int>::iterator> best_vertices; // new, second
            std::list<int>::iterator best_position_for_vertex; // index of the element before which we should insert

            for (int v_new: free_nodes)
            {
                best_cost = std::numeric_limits<int>::max();

                for (auto it = second_cycle.begin(); it != second_cycle.end(); it++)
                {
                    v1 = it;
                    v2 = std::next(it) != second_cycle.end() ? std::next(it) : second_cycle.begin();

                    cost = distance_matrix[*v1][v_new] + distance_matrix[v_new][*v2] - distance_matrix[*v1][*v2];

                    if (cost < best_cost){
                        second_best_cost = best_cost;
                        best_cost = cost;
                        best_position_for_vertex = v2;
                    }
                }
                regret = second_best_cost - best_cost;
                if (regret > highest_regret)
                {
                    highest_regret = regret;
                    best_vertices = {v_new, best_position_for_vertex};
                }
            }
            second_cycle.insert(best_vertices.second, best_vertices.first);
            free_nodes.remove(best_vertices.first);
        }

    }

    return std::pair(first_cycle, second_cycle);

}



int main(){

    std::vector<Node> nodes_corrdinats = read_data("kroB100.tsp");
    
    /*for (auto i: nodes_corrdinats){
        std::cout << i.id <<" "<< i.x <<" "<< i.y << std::endl;
    }

    std::cout << count_euclidean_distance(nodes_corrdinats[0], nodes_corrdinats[0]) << std::endl; */

    std::vector<std::vector<int>> distance_matrix = create_distance_matrix(nodes_corrdinats);
        

    for (auto i: distance_matrix){
        for (auto j: i){
            std::cout << j << " ";
        }
        std::cout<< std::endl;
    }
    // std::pair<std::list<int>, std::list<int>> ca = create_two_tsp_cycles_greedy_cycle(distance_matrix);
    // std::cout<<"length1 : "<<cycle_length(distance_matrix, ca.first) <<" length2 : "<<cycle_length(distance_matrix, ca.second)<<"\n"; 

    // std::pair<std::list<int>, std::list<int>> c = create_two_tsp_cycles(distance_matrix);
    // std::cout<<"length1 : "<<cycle_length(distance_matrix, c.first) <<" length2 : "<<cycle_length(distance_matrix, c.second)<<"\n"; 

    std::pair cycles = create_two_tsp_cycles_regret_heurystic(distance_matrix);
    for (auto i: cycles.first){
        std::cout << i << " ";
    }   
    std::cout << std::endl;


    for (auto i: cycles.second){
        std::cout << i << " " ;
    }   
    std::cout << std::endl;

    /*
    std::cout << "Testing: " <<cycle_length(distance_matrix, {0, 1, 2, 0}) << "\n";
    std::cout << find_min_index_without_list({4,0,1,8,3}, {1,3}) << std::endl;
    std::cout << find_min_index_without_list({4,0,1,8,3}, {}) << std::endl;
    std::cout << find_min_index_without_list({}, {}) << std::endl;
    */

    return 0;
}
