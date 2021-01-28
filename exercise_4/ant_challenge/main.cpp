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

void testcase() {
    int n; std::cin >> n;
    int e; std::cin >> e;
    int s; std::cin >> s;
    int a; std::cin >> a;
    int b; std::cin >> b;
    std::vector<weighted_graph> graphs(s, weighted_graph{});
    
    for (int i = 0; i < e; i++) {
        int u; std::cin >> u;
        int v; std::cin >> v;
        
        for (int j = 0; j < s; j++) {
            int w; std::cin >> w;
            boost::add_edge(u, v, w, graphs[j]);
        }
    }
    
    std::vector<std::vector<edge_descriptor>> msts(s, std::vector<edge_descriptor>{});
    weighted_graph solutionGraph{};
    
    for (int i = 0; i < s; i++) {
        int h; std::cin >> h;
        std::vector<edge_descriptor> mst{};
        boost::kruskal_minimum_spanning_tree(graphs[i], std::back_inserter(mst));
        
        for (edge_descriptor edge : mst) {
            int weight = boost::get(boost::edge_weight, graphs[i], edge);
            auto source = boost::source(edge, graphs[i]);
            auto target = boost::target(edge, graphs[i]);
            auto edgetupple = boost::add_edge(source, target, weight, solutionGraph);
            
            if (!edgetupple.second) {
                auto weightMap = boost::get(boost::edge_weight, solutionGraph);
                weightMap[edgetupple.first] = std::min(weight, weightMap[edgetupple.first]);
            }
        }
    }
    
    std::vector<int> distanceMap(n);
    boost::dijkstra_shortest_paths(solutionGraph, a,
        boost::distance_map(boost::make_iterator_property_map(distanceMap.begin(),
            boost::get(boost::vertex_index, solutionGraph))));
    std::cout << distanceMap[b] << std::endl;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    int t; std::cin >> t;
    
    for (int i = 0; i < t; i++) {
        testcase();
    }
}
