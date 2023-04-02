#include <iostream>
#include <fstream>
#include <vector>
#include <string.h>
#include <sstream>
#include <math.h>

#include"../includes/read_data.h"


std::vector<Node> read_data(std::string file_name){
    
    std::ifstream file(file_name);
    std::vector<Node> nodes;

    std::string line;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        int x, y, z;
        if (iss >> x >> y >> z) {
            Node n = {x, y, z};
            nodes.push_back(n);
        }
    }

    return nodes;
}

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
