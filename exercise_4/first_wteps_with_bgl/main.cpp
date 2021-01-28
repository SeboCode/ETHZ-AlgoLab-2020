#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>
#include <boost/graph/kruskal_min_spanning_tree.hpp>
#include <boost/graph/dijkstra_shortest_paths.hpp>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/properties.hpp>

typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::undirectedS,
                              boost::no_property,
                              boost::property<boost::edge_weight_t, int>
                              > weighted_graph;
typedef boost::graph_traits<weighted_graph>::edge_descriptor edge_descriptor;
typedef boost::graph_traits<weighted_graph>::vertex_descriptor vertex_descriptor;

void testcase() {
    int n; std::cin >> n;
    int m; std::cin >> m;
    weighted_graph graph{};
    
    for (int i = 0; i < m; i++) {
        int u; std::cin >> u;
        int v; std::cin >> v;
        int w; std::cin >> w;
        boost::add_edge(u, v, w, graph);
    }
    
    std::vector<edge_descriptor> mst{};
    boost::kruskal_minimum_spanning_tree(graph, std::back_inserter(mst));
    int mstSum = 0;
    
    for (edge_descriptor mstEdge : mst) {
        mstSum += boost::get(boost::edge_weight, graph, mstEdge);
    }
    
    std::vector<int> vertexDistance(n);
    boost::dijkstra_shortest_paths(graph, 0,
        boost::distance_map(boost::make_iterator_property_map(vertexDistance.begin(),
            boost::get(boost::vertex_index, graph))));
            
    int maxDistance = *(std::max_element(vertexDistance.cbegin(), vertexDistance.cend()));
    std::cout << mstSum << " " << maxDistance << std::endl;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    int t; std::cin >> t;
    
    for (int i = 0; i < t; i++) {
        testcase();
    }
}
