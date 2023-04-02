#include <iostream>
#include <vector>
#include <math.h>
#include <list>
#include <map> 
#include <assert.h>
#include <algorithm>
#include <iostream>
#include <random>
#include <vector>

#include "read_data.cpp"
#include "regret_heuristic.cpp"
#include "local_search.cpp"

void save_data(std::vector<Node> nodes_corrdinats, std::list<int> cycle, std::string file_name){
    std::fstream file;
    file.open(file_name, std::ios::out);
    int prev = -1;
    for (auto it = cycle.begin(); it != cycle.end(); ++it){
        file << nodes_corrdinats[*it].x<<" "<<nodes_corrdinats[*it].y<<"\n";
    }
    return;
}

std::vector<int> vertex_replacment(std::vector<int> path, int random_start, int random_to){ // random statment are not lots to easy testing
    std::swap(path[random_start], path[random_to]);
    return path;
}

std::vector<int> greedy_local_search_vertex(std::vector<int> staring_path, std::vector<std::vector<int>> distance_matrix){

    std::vector<int> best_path = staring_path;
    auto rd = std::random_device {}; 
    auto rng = std::default_random_engine { rd() };
    int counter = 0;
    while (counter < 1000){
        counter ++;
        int random_start = rand() % (staring_path.size() - 2) + 1;
        int random_to;
        do{
            random_to = rand() % (staring_path.size() - 2) + 1;
        } while(random_start != random_to); 
        std::vector<int> propose_path = vertex_replacment(best_path, random_start, random_to);
        if (count_delta_function(distance_matrix, best_path, propose_path) < 0){
            return propose_path;
        }
    }
}

std::pair<std::vector<int>, std::vector<int>> greedy_local_search_for_pair_vertex(std::pair<std::list<int>, std::list<int>> staring_paths, std::vector<std::vector<int>> distance_matrix){

    return std::pair(greedy_local_search_vertex(std::vector(staring_paths.first.begin(), staring_paths.first.end()), distance_matrix), greedy_local_search_vertex(std::vector(staring_paths.second.begin(), staring_paths.second.end()), distance_matrix));

}


std::vector<int> best_from_all_vertex(std::vector<int> staring_path, std::vector<std::vector<int>> distance_matrix){

    std::vector<int> best_path = staring_path;

    for (int random_start = 0;random_start<staring_path.size();random_start++){
        for (int random_to = random_start + 1; random_to<staring_path.size();random_to++){
            // int random_start = rand() % staring_path.size();
            // int random_to = rand()%(staring_path.size()-random_start + 1) + random_start;
            if(random_start == random_to) continue;;
            std::vector<int> propose_path = vertex_replacment(best_path, random_start, random_to);
            if (count_delta_function(distance_matrix, best_path, propose_path) < 0){
                best_path = propose_path;
            }
        }
    }
    return best_path;

}

std::vector<int>steepest_local_search_vertex(std::vector<int> staring_path, std::vector<std::vector<int>> distance_matrix){

    std::vector<int> best_path = staring_path;
    // do puki jest poprawa, dla każdeg owierzchołka licze delte i wybieram najelpepsze i aplikuje jeśli delta jest dodatnia a jak nie to stopuje o koniec 
    while (true){
        std::vector<int> propose_path = best_from_all_vertex(staring_path, distance_matrix);
        if (count_delta_function(distance_matrix, best_path, propose_path) < 0){
            best_path = propose_path;
        }
        else{
            return best_path;
        }
    }
}


std::pair<std::vector<int>, std::vector<int>> steepest_local_search_for_pair_vertex(std::pair<std::list<int>, std::list<int>> staring_paths, std::vector<std::vector<int>> distance_matrix){
    std::vector<int> a = steepest_local_search_vertex(std::vector(staring_paths.first.begin(), staring_paths.first.end()), distance_matrix);
    std::vector<int> b = steepest_local_search_vertex(std::vector(staring_paths.second.begin(), staring_paths.second.end()), distance_matrix);
    return std::pair(a, b);

}



/*
#include "../includes/read_data.h"
#include "../includes/regret_heuristic.h"
#include "../includes/local_search.h"
*/

std::pair<std::vector<int>, std::vector<int>> vertex2_replacment(std::vector<int> path, std::vector<int> path2, int random_start, int random_to){ // random statment are not lots to easy testing

    int helper = path[random_start];
    path[random_start] = path2[random_to];
    path2[random_to] = helper;
    return std::pair(path, path2);
}

std::pair<std::vector<int>, std::vector<int>> greedy_local_search_vertex2(std::vector<int> staring_path, std::vector<int> staring_path2, std::vector<std::vector<int>> distance_matrix){

    std::vector<int> best_path = staring_path;
    std::vector<int> best_path2 = staring_path2;
    auto rd = std::random_device {}; 
    auto rng = std::default_random_engine { rd() };
    int counter = 0;
    while (counter < 100){
        counter ++;
        int random_start = rand() % (staring_path.size() - 2) + 1;
        int random_to = rand() % (staring_path.size() - 2) + 1;
        std::pair<std::vector<int>, std::vector<int>> propose_paths = vertex2_replacment(best_path, best_path2, random_start, random_to);
        if (count_delta_function(distance_matrix, best_path, propose_paths.first) + count_delta_function(distance_matrix, best_path2, propose_paths.second) < 0){
            return propose_paths;
        }
    }
}

std::pair<std::vector<int>, std::vector<int>> best_from_all_vertex2(std::vector<int> staring_path, std::vector<int> staring_path2, std::vector<std::vector<int>> distance_matrix){

    std::pair<std::vector<int>, std::vector<int>> best_paths = std::pair(staring_path, staring_path2);

    for (int random_start = 0;random_start<staring_path.size();random_start++){
        for (int random_to = 0; random_to<staring_path.size();random_to++){
            // int random_start = rand() % staring_path.size();
            // int random_to = rand()%(staring_path.size()-random_start + 1) + random_start;
            std::pair<std::vector<int>, std::vector<int>> propose_paths = vertex2_replacment(best_paths.first, best_paths.second, random_start, random_to);
        if (count_delta_function(distance_matrix, best_paths.first, propose_paths.first) + count_delta_function(distance_matrix, best_paths.second, propose_paths.second) < 0){
                best_paths = propose_paths;
            }
        }
    }
    return best_paths;

}

std::pair<std::vector<int>, std::vector<int>>steepest_local_search_vertex2(std::pair<std::vector<int>, std::vector<int>> staring_paths, std::vector<std::vector<int>> distance_matrix){

    std::pair<std::vector<int>, std::vector<int>> best_paths = staring_paths;
    // do puki jest poprawa, dla każdeg owierzchołka licze delte i wybieram najelpepsze i aplikuje jeśli delta jest dodatnia a jak nie to stopuje o koniec 
    while (true){
        std::pair<std::vector<int>, std::vector<int>> propose_paths = best_from_all_vertex2(staring_paths.first, staring_paths.second, distance_matrix);
        if (count_delta_function(distance_matrix, best_paths.first, propose_paths.first) + count_delta_function(distance_matrix, best_paths.second, propose_paths.second) < 0){
            best_paths = propose_paths;
        }
        else{
            return best_paths;
        }
    }
}

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


    std::vector<Node> nodes_corrdinats = read_data("../kroA100.tsp");
    std::vector<std::vector<int>> distance_matrix = create_distance_matrix(nodes_corrdinats);
    std::pair cycles_list = create_two_tsp_cycles_regret_heurystic(distance_matrix, 0);

    std::cout<<"regret heuristic: length1 : "<<cycle_length(distance_matrix, cycles_list.first) <<" length2 : "<<cycle_length(distance_matrix, cycles_list.second)<<"\n"; 
    std::pair<std::vector<int>, std::vector<int>> cycles;
    cycles.first = std::vector(std::begin(cycles_list.first), std::end(cycles_list.first));
    cycles.second = std::vector(std::begin(cycles_list.second), std::end(cycles_list.second));

    std::pair<std::vector<int>, std::vector<int>> greedy_paths = greedy_local_search_vertex2(cycles.first, cycles.second, distance_matrix);
    std::cout<<"greedy local searchv: length1 : "<<cycle_length(distance_matrix, std::list(greedy_paths.first.begin(), greedy_paths.first.end())) <<" length2 : "<<cycle_length(distance_matrix, std::list(greedy_paths.second.begin(), greedy_paths.second.end()))<<"\n"; 

    save_data(nodes_corrdinats, std::list(greedy_paths.first.begin(), greedy_paths.first.end()), "between_greedy1.txt");
    save_data(nodes_corrdinats, std::list(greedy_paths.second.begin(), greedy_paths.second.end()), "between_greedy2.txt");

    std::pair<std::vector<int>, std::vector<int>> steepeset_paths = steepest_local_search_vertex2(cycles, distance_matrix);
    std::cout<<"steeepsetlength1v : "<<cycle_length(distance_matrix, std::list(steepeset_paths.first.begin(), steepeset_paths.first.end())) <<" length2 : "<<cycle_length(distance_matrix, std::list(steepeset_paths.second.begin(), steepeset_paths.second.end()))<<"\n"; 

    save_data(nodes_corrdinats, std::list(steepeset_paths.first.begin(), steepeset_paths.first.end()), "between_steep1.txt");
    save_data(nodes_corrdinats, std::list(steepeset_paths.second.begin(), steepeset_paths.second.end()), "between_steep2.txt");

    return 0;
}
