#include <iostream>
#include <vector>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/kruskal_min_spanning_tree.hpp>

typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::undirectedS,
    boost::no_property,
        boost::property<boost::edge_weight_t, int>> weighted_graph;
typedef boost::graph_traits<weighted_graph>::edge_descriptor edge_desc;
typedef boost::graph_traits<weighted_graph>::vertex_descriptor vertex_desc;

int mstValue(edge_desc& edge, weighted_graph& graph) {
    auto weight_map = boost::get(boost::edge_weight, graph);
    std::vector<edge_desc> mst;
    vertex_desc source = boost::source(edge, graph);
    vertex_desc target = boost::target(edge, graph);
    int weight = weight_map[edge];
    boost::remove_edge(edge, graph);
    boost::kruskal_minimum_spanning_tree(graph, std::back_inserter(mst));
    boost::add_edge(source, target, weight, graph);
    int total = 0;
    
    for (auto it = mst.begin(); it != mst.end(); it++) {
        total += weight_map[*it];
    }
    
    return total;
}

void testcase() {
    int n; std::cin >> n;
    int i; std::cin >> i;
    weighted_graph graph(n);
    
    for (int i = 0; i < n; i++) {
        for (int j = i+1; j < n; j++) {
            int cost; std::cin >> cost;
            boost::add_edge(i, j, cost, graph);
       }
    }
    
    std::vector<edge_desc> mst;
    boost::kruskal_minimum_spanning_tree(graph, std::back_inserter(mst));
    int total = -1;
    
    for (auto it = mst.begin(); it != mst.end(); it++) {
        int value = mstValue(*it, graph);
        
        if (total == -1) {
            total = value;
        } else {
            total = std::min(total, value);
        }
    }
    
    std::cout << total << std::endl;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    int t; std::cin >> t;
    
    for (int i = 0; i < t; i++) {
        testcase();
    }
}
