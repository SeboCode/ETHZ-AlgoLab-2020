#include <iostream>
#include <boost/graph/push_relabel_max_flow.hpp>
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

int max = 100;

void testcase() {
    int N; std::cin >> N;
    int M; std::cin >> M;
    int S; std::cin >> S;
    graph_type graph(N + M + S);
    EdgeAdder edgeAdder(graph);
    vertex_descriptor const source = boost::add_vertex(graph);
    vertex_descriptor const target = boost::add_vertex(graph);
    
    for (int i = 0; i < S; i++) {
        int l; std::cin >> l;
        edgeAdder.addEdge(N + M + i, target, l, 0);
    }
    
    for (int i = 0; i < M; i++) {
        int s; std::cin >> s;
        edgeAdder.addEdge(N + i, N + M + (s-1), 1, 0);
    }
    
    for (int i = 0; i < N; i++) {
        edgeAdder.addEdge(source, i, 1, max);
        
        for (int j = 0; j < M; j++) {
            int b; std::cin >> b;
            edgeAdder.addEdge(i, N + j, 1, max - b);
        }
    }
    
    boost::successive_shortest_path_nonnegative_weights(graph, source, target);
    out_edge_iterator e, eend;
    int flow = 0;
    auto c_map = boost::get(boost::edge_capacity, graph);
    auto rc_map = boost::get(boost::edge_residual_capacity, graph);
    
    for (boost::tie(e, eend) = boost::out_edges(source, graph); e != eend; e++) {
        flow += c_map[*e] - rc_map[*e];
    }
    
    std::cout << flow << ' ' << flow * max * 2 - boost::find_flow_cost(graph) << std::endl;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    int T; std::cin >> T;
    
    for (int i = 0; i < T; i++) {
        testcase();
    }
}
