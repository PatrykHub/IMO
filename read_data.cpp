#include <iostream>
#include <fstream>
#include <vector>
#include <string.h>
#include <sstream>


struct Node {
      int id, x, y; 
};

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
