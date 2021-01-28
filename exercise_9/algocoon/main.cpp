#include <iostream>
#include <algorithm>
#include <boost/graph/push_relabel_max_flow.hpp>
#include <boost/graph/adjacency_list.hpp>

typedef boost::adjacency_list_traits<boost::vecS, boost::vecS, boost::directedS> traits;
typedef traits::vertex_descriptor vertex_descriptor;
typedef traits::edge_descriptor edge_descriptor;
typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::directedS,
    boost::no_property,
    boost::property<boost::edge_capacity_t, long,
        boost::property<boost::edge_residual_capacity_t, long,
            boost::property<boost::edge_reverse_t, edge_descriptor>>>> graph_type;

struct EdgeAdder {
    explicit EdgeAdder(graph_type &graph) : graph(graph) {}
        
    void addEdge(int from, int to, long capacity) {
        auto c_map = boost::get(boost::edge_capacity, graph);
        auto r_map = boost::get(boost::edge_reverse, graph);
        const auto e = boost::add_edge(from, to, graph).first;
        const auto rev_e = boost::add_edge(to, from, graph).first;
        c_map[e] = capacity;
        c_map[rev_e] = 0;
        r_map[e] = rev_e;
        r_map[rev_e] = e;
    }
    
    private:
        graph_type &graph;
};

void testcase() {
    int n; std::cin >> n;
    int m; std::cin >> m;
    graph_type graph(n);
    EdgeAdder edgeAdder(graph);
    
    for (int i = 0; i < m; i++) {
        int a; std::cin >> a;
        int b; std::cin >> b;
        int c; std::cin >> c;
        edgeAdder.addEdge(a, b, c);
    }
    
    int minCost = boost::push_relabel_max_flow(graph, 0, n-1);
    
    for (int i = 1; i < n; i++) {
        minCost = std::min(minCost, (int) boost::push_relabel_max_flow(graph, 0, i));
        minCost = std::min(minCost, (int) boost::push_relabel_max_flow(graph, i, 0));
    }
    
    std::cout << minCost << std::endl;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    int t; std::cin >> t;
    
    for (int i = 0; i < t; i++) {
        testcase();
    }
}
