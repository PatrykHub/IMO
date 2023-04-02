#include <iostream>
#include <vector>
#include <list>
#include <algorithm>
  #include <bitset>
  #include <complex>
  #include <deque>
  #include <exception>
  #include <fstream>
  #include <functional>
  #include <iomanip>
  #include <ios>
  #include <iosfwd>
  #include <iostream>
  #include <istream>
  #include <iterator>
  #include <limits>
  #include <list>
  #include <locale>
  #include <map>
  #include <memory>
  #include <new>
  #include <numeric>
  #include <ostream>
  #include <queue>
  #include <set>
  #include <sstream>
  #include <stack>
  #include <stdexcept>
  #include <streambuf>
  #include <string>
  #include <typeinfo>
  #include <utility>
  #include <valarray>
  #include <vector>
#include"../includes/regret_heuristic.h"


int find_min_index_with_included_indexes(std::vector<int> vec, std::list<int> included_indexes){

    int min_value = INT_MAX; 
    int min_inex;

    for (int i : included_indexes) {
        if (i >= 0 && i < vec.size()) { 
            if (vec[i] < min_value) {
                min_value = vec[i];
                min_inex = i;
            }
        }
    }

    return min_inex;
}


std::pair<std::list<int>, std::list<int>> create_two_tsp_cycles_regret_heurystic(std::vector<std::vector<int>> distance_matrix, int starting_index){ 
    

    std::list <int> first_cycle, second_cycle, banned;
    std::list<int> free_nodes(distance_matrix[0].size());
    
    std::iota(free_nodes.begin(), free_nodes.end(), 0);

    int init_node_ferst_cycle = starting_index; // you cen make it random 
    free_nodes.remove(init_node_ferst_cycle);
    first_cycle.push_back(init_node_ferst_cycle);
    int secend_node_ferst_cycle = find_min_index_with_included_indexes(distance_matrix[init_node_ferst_cycle], free_nodes);
    free_nodes.remove(secend_node_ferst_cycle);
    first_cycle.push_back(secend_node_ferst_cycle);

    int init_node_secend_cycle = std::distance(distance_matrix[init_node_ferst_cycle].begin(),std::max_element(distance_matrix[init_node_ferst_cycle].begin(), distance_matrix[init_node_ferst_cycle].end()));
    free_nodes.remove(init_node_secend_cycle);
    second_cycle.push_back(init_node_secend_cycle);
    int secend_node_secend_cycle = find_min_index_with_included_indexes(distance_matrix[init_node_secend_cycle], free_nodes);
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
            std::pair<int, std::list<int>::iterator> best_vertices;
            std::list<int>::iterator best_position_for_vertex;

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
            std::pair<int, std::list<int>::iterator> best_vertices;
            std::list<int>::iterator best_position_for_vertex;

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
