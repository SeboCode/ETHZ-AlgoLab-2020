#include <iostream>
#include <vector>
#include <boost/graph/max_cardinality_matching.hpp>
#include <boost/graph/adjacency_list.hpp>

typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::undirectedS> graph_type;
typedef boost::graph_traits<graph_type>::vertex_descriptor vertex_descriptor;
typedef boost::graph_traits<graph_type>::edge_descriptor edge_descriptor;

void testcase() {
    int n; std::cin >> n;
    std::vector<std::vector<bool>> isField(n, std::vector<bool>(n, false));
    int fieldCount = 0;
    
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            int fieldValue; std::cin >> fieldValue;
            
            if (fieldValue == 1) {
                isField[i][j] = true;
                fieldCount++;
            }
        }
    }
    
    graph_type graph(n * n);
    
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (!isField[i][j]) {
                continue;
            }
            
            int currentVertex = i * n + j;
            
            if (i - 1 >= 0 && j - 2 >= 0 && isField[i-1][j-2]) {
                boost::add_edge(currentVertex, (i-1) * n + j-2, graph);
            }
            
            if (i - 1 >= 0 && j + 2 < n && isField[i-1][j+2]) {
                boost::add_edge(currentVertex, (i-1) * n + j+2, graph);
            }
            
            if (i - 2 >= 0 && j - 1 >= 0 && isField[i-2][j-1]) {
                boost::add_edge(currentVertex, (i-2) * n + j-1, graph);
            }
            
            if (i - 2 >= 0 && j + 1 < n && isField[i-2][j+1]) {
                boost::add_edge(currentVertex, (i-2) * n + j+1, graph);
            }
        }
    }
    
    std::vector<vertex_descriptor> mateMap(n * n);
    boost::edmonds_maximum_cardinality_matching(graph,
        boost::make_iterator_property_map(mateMap.begin(),
            boost::get(boost::vertex_index, graph)));
    int buddyCount = boost::matching_size(graph,
        boost::make_iterator_property_map(mateMap.begin(),
            boost::get(boost::vertex_index, graph)));
    std::cout << fieldCount - buddyCount << std::endl;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    int t; std::cin >> t;
    
    for (int i = 0; i < t; i++) {
        testcase();
    }
}
