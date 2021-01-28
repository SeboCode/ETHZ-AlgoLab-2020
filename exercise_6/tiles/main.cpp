#include <iostream>
#include <vector>
#include <boost/graph/max_cardinality_matching.hpp>
#include <boost/graph/adjacency_list.hpp>

typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::undirectedS> graph_type;
typedef boost::graph_traits<graph_type>::vertex_descriptor vertex_descriptor;

void testcase() {
    int w; std::cin >> w;
    int h; std::cin >> h;
    std::vector<std::vector<bool>> needsTile(h, std::vector<bool>(w, false));
    int tilePlacesCount = 0;
    
    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) {
            char element; std::cin >> element;
            
            if (element == '.') {
                needsTile[i][j] = true;
                tilePlacesCount++;
            }
        }
    }
    
    if (tilePlacesCount % 2 != 0) {
        std::cout << "no" << std::endl;
        return;
    }
    
    graph_type graph(h * w);
    
    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) {
            vertex_descriptor const current = i * w + j;
            
            // tile-combination to the right
            if (j < w - 1 && needsTile[i][j] && needsTile[i][j+1]) {
                vertex_descriptor const right = i * w + (j + 1);
                boost::add_edge(current, right, graph);
            }
            
            //tile-combination to the bottom
            if (i < h - 1 && needsTile[i][j] && needsTile[i+1][j]) {
                vertex_descriptor const bellow = (i + 1) * w + j;
                boost::add_edge(current, bellow, graph);
            }
        }
    }
    
    std::vector<vertex_descriptor> mateMap(h * w);
    boost::edmonds_maximum_cardinality_matching(graph,
        boost::make_iterator_property_map(mateMap.begin(),
            boost::get(boost::vertex_index, graph)));
    int buddyCount = boost::matching_size(graph,
        boost::make_iterator_property_map(mateMap.begin(),
            boost::get(boost::vertex_index, graph)));
    
    if (tilePlacesCount / 2 == buddyCount) {
        std::cout << "yes" << std::endl;
    } else {
        std::cout << "no" << std::endl;
    }
}

int main() {
    std::ios_base::sync_with_stdio(false);
    int t; std::cin >> t;
    
    for (int i = 0; i < t; i++) {
        testcase();
    }
}
