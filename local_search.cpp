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