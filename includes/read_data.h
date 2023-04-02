#include <vector>
#include <string.h>
#include <sstream>

struct Node {
      int id, x, y; 
};

std::vector<Node> read_data(std::string file_name);

int count_euclidean_distance(Node node_1, Node node_2);

std::vector<std::vector<int>> create_distance_matrix(std::vector<Node> nodes_corrdinats);