#include <iostream>
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
    int s; std::cin >> s;
    graph_type graph(n);
    EdgeAdder edgeAdder(graph);
    vertex_descriptor const source = 0;
    vertex_descriptor const target = boost::add_vertex(graph);
    
    for (int i = 0; i < s; i++) {
        int storeLocation; std::cin >> storeLocation;
        edgeAdder.addEdge(storeLocation, target, 1);
    }
    
    for (int i = 0; i < m; i++) {
        int from; std::cin >> from;
        int to; std::cin >> to;
        edgeAdder.addEdge(from, to, 1);
        edgeAdder.addEdge(to, from, 1);
    }
    
    long flow = boost::push_relabel_max_flow(graph, source, target);
    
    if (flow == s) {
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
