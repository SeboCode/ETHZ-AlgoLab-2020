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
    int l; std::cin >> l;
    int p; std::cin >> p;
    graph_type graph(l);
    EdgeAdder edgeAdder(graph);
    vertex_descriptor const source = boost::add_vertex(graph);
    vertex_descriptor const target = boost::add_vertex(graph);
    long totalDemand = 0;
    
    for (int i = 0; i < l; i++) {
        int g; std::cin >> g;
        int d; std::cin >> d;
        edgeAdder.addEdge(source, i, g);
        edgeAdder.addEdge(i, target, d);
        totalDemand += d;
    }
    
    for (int i = 0; i < p; i++) {
        int f; std::cin >> f;
        int t; std::cin >> t;
        int c; std::cin >> c;
        int C; std::cin >> C;
        edgeAdder.addEdge(f, target, c);
        edgeAdder.addEdge(source, t, c);
        edgeAdder.addEdge(f, t, C - c);
        totalDemand += c;
    }
    
    long flow = boost::push_relabel_max_flow(graph, source, target);
    
    if (flow == totalDemand) {
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
