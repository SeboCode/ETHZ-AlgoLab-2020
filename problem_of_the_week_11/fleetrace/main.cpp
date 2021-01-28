#include <iostream>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/successive_shortest_path_nonnegative_weights.hpp>
#include <boost/graph/find_flow_cost.hpp>

typedef boost::adjacency_list_traits<boost::vecS, boost::vecS, boost::directedS> traits;
typedef traits::vertex_descriptor vertex_descriptor;
typedef traits::edge_descriptor edge_descriptor;
typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::directedS,
    boost::no_property,
    boost::property<boost::edge_capacity_t, long,
        boost::property<boost::edge_residual_capacity_t, long,
            boost::property<boost::edge_reverse_t, edge_descriptor,
                boost::property<boost::edge_weight_t, long>>>>> graph_type;
typedef boost::graph_traits<graph_type>::out_edge_iterator out_edge_iterator;

struct EdgeAdder {
    explicit EdgeAdder(graph_type &graph) : graph(graph) {}
    
    void addEdge(int from, int to, long capacity, long cost) {
        auto c_map = boost::get(boost::edge_capacity, graph);
        auto r_map = boost::get(boost::edge_reverse, graph);
        auto w_map = boost::get(boost::edge_weight, graph);
        const edge_descriptor e = boost::add_edge(from, to, graph).first;
        const edge_descriptor rev_e = boost::add_edge(to, from, graph).first;
        c_map[e] = capacity;
        c_map[rev_e] = 0;
        r_map[e] = rev_e;
        r_map[rev_e] = e;
        w_map[e] = cost;
        w_map[rev_e] = -cost;
    }
    
    private:
        graph_type &graph;
};

int max = 50;

void testcase() {
    int b; std::cin >> b;
    int s; std::cin >> s;
    int p; std::cin >> p;
    graph_type graph(b + s);
    EdgeAdder edgeAdder(graph);
    vertex_descriptor const source = boost::add_vertex(graph);
    vertex_descriptor const target = boost::add_vertex(graph);
    
    for (int i = 0; i < b; i++) {
        edgeAdder.addEdge(source, i, 1, 0);
        edgeAdder.addEdge(i, target, 1, max);
    }
    
    for (int i = 0; i < s; i++) {
        edgeAdder.addEdge(b + i, target, 1, 0);
    }
    
    for (int i = 0; i < p; i++) {
        int b_i; std::cin >> b_i;
        int s_i; std::cin >> s_i;
        int c_i; std::cin >> c_i;
        edgeAdder.addEdge(b_i, b + s_i, 1, max - c_i);
    }
    
    boost::successive_shortest_path_nonnegative_weights(graph, source, target);
    std::cout << b * max - boost::find_flow_cost(graph) << std::endl;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    int t; std::cin >> t;
    
    for (int i = 0; i < t; i++) {
        testcase();
    }
}
