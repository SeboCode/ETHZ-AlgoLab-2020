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
    graph_type graph(n);
    EdgeAdder edgeAdder(graph);
    vertex_descriptor const source = boost::add_vertex(graph);
    vertex_descriptor const target = boost::add_vertex(graph);
    int positiveSum = 0;
    
    for (int i = 0; i < n; i++) {
        int b; std::cin >> b;
        
        if (b >= 0) {
            edgeAdder.addEdge(source, i, b);
            positiveSum += b;
        } else {
            edgeAdder.addEdge(i, target, -b);
        }
    }
    
    for (int k = 0; k < m; k++) {
        int i; std::cin >> i;
        int j; std::cin >> j;
        int d; std::cin >> d;
        edgeAdder.addEdge(i, j, d);
    }
    
    // We use max. flow = min. cut here. An upper bound on the flow is the sum
    // of the capacities of the outgoing edges of the source. In case we reach
    // that value, we either have a negative final balance or a balance of
    // exactly 0. In both cases, the condition of the exercise is not met, as
    // we require the final balance to be STRICTLY larger than the final debt,
    // which itself is at least 0.
    if (boost::push_relabel_max_flow(graph, source, target) < positiveSum) {
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
