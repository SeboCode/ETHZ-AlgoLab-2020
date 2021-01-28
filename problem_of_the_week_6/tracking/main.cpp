#include <iostream>
#include <boost/graph/dijkstra_shortest_paths.hpp>
#include <boost/graph/adjacency_list.hpp>

typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::undirectedS,
                              boost::no_property,
                              boost::property<boost::edge_weight_t, int>
                              > weighted_graph;

void testcase() {
    int n; std::cin >> n;
    int m; std::cin >> m;
    int k; std::cin >> k;
    int x; std::cin >> x;
    int y; std::cin >> y;
    weighted_graph graph(n * (k + 1));
    
    for (int i = 0; i < m; i++) {
        int a; std::cin >> a;
        int b; std::cin >> b;
        int c; std::cin >> c;
        int d; std::cin >> d;
        
        for (int j = 0; j <= k; j++) {
            if (d == 1 && j < k) {
                boost::add_edge(a + j * n, b + (j + 1) * n, c, graph);
                boost::add_edge(a + (j + 1) * n, b + j * n, c, graph);
            } else {
                boost::add_edge(a + j * n, b + j * n, c, graph);
            }
        }
    }
    
    std::vector<int> distanceMap(n * (k + 1));
    boost::dijkstra_shortest_paths(graph, x,
        boost::distance_map(boost::make_iterator_property_map(distanceMap.begin(),
            boost::get(boost::vertex_index, graph))));
    std::cout << distanceMap[y + k * n] << std::endl;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    int t; std::cin >> t;
    
    for (int i = 0; i < t; i++) {
        testcase();
    }
}
