#include <iostream>
#include <limits>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/successive_shortest_path_nonnegative_weights.hpp>
#include <boost/graph/find_flow_cost.hpp>
#include <boost/graph/push_relabel_max_flow.hpp>

typedef boost::adjacency_list_traits<boost::vecS, boost::vecS, boost::directedS> traits;
typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::directedS,
    boost::no_property,boost::property<boost::edge_capacity_t, long,
        boost::property<boost::edge_residual_capacity_t, long,
            boost::property<boost::edge_reverse_t, traits::edge_descriptor,
                boost::property<boost::edge_weight_t, long>>>>> graph_type;
typedef traits::vertex_descriptor vertex_desc;
typedef traits::edge_descriptor edge_desc;

class edge_adder {
    graph_type &G;
    
    public:
        explicit edge_adder(graph_type &G) : G(G) {}
        
        void add_edge(int from, int to, long capacity, long cost) {
            auto c_map = boost::get(boost::edge_capacity, G);
            auto r_map = boost::get(boost::edge_reverse, G);
            auto w_map = boost::get(boost::edge_weight, G);
            const auto e = boost::add_edge(from, to, G).first;
            const auto rev_e = boost::add_edge(to, from, G).first;
            c_map[e] = capacity;
            c_map[rev_e] = 0;
            r_map[e] = rev_e;
            r_map[rev_e] = e;
            w_map[e] = cost;
            w_map[rev_e] = -cost;
        }
};

void reset_source_edge_capacity(edge_desc const & e, edge_desc const & rev_e, long capacity, graph_type & G) {
    auto c_map = boost::get(boost::edge_capacity, G);
    auto r_map = boost::get(boost::edge_reverse, G);
    auto w_map = boost::get(boost::edge_weight, G);
    c_map[e] = capacity;
    c_map[rev_e] = 0;
    r_map[e] = rev_e;
    r_map[rev_e] = e;
    w_map[e] = 0;
    w_map[rev_e] = 0;
}

void testcase() {
    int c; std::cin >> c;
    int g; std::cin >> g;
    long b; std::cin >> b;
    int k; std::cin >> k;
    int a; std::cin >> a;
    graph_type graph(c);
    edge_adder adder(graph);
    vertex_desc const source = boost::add_vertex(graph);
    edge_desc const source_edge = boost::add_edge(source, k, graph).first;
    edge_desc const source_rev_edge = boost::add_edge(k, source, graph).first;
    
    for (int i = 0; i < g; i++) {
        int x; std::cin >> x;
        int y; std::cin >> y;
        int d; std::cin >> d;
        int e; std::cin >> e;
        adder.add_edge(x, y, e, d);
    }
    
    boost::successive_shortest_path_nonnegative_weights(graph, k, a);
    
    // This check is necessary, since in this case the limiting factor will be
    // the flow and not the cost. The binary search bellow will compute wrong
    // results, since it expects the cost to be the limiting factor (we would
    // always satisfy the first condition and thus always increase left).
    if (b >= boost::find_flow_cost(graph)) {
        // Needed, otherwise push_relabel_max_flow will throw a segmentation fault.
        reset_source_edge_capacity(source_edge, source_rev_edge, 0, graph);
        std::cout << boost::push_relabel_max_flow(graph, k, a) << std::endl;
        return;
    }
    
    int left = 0;
    int right = std::numeric_limits<int>::max();
    
    while (left < right) {
        int middle = (right + left + 1) / 2;
        reset_source_edge_capacity(source_edge, source_rev_edge, middle, graph);
        boost::successive_shortest_path_nonnegative_weights(graph, source, a);
        long cost = boost::find_flow_cost(graph);
        
        if (b >= cost) {
            left = middle;
        } else {
            right = middle-1;
        }
    }
    
    std::cout << left << std::endl;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    int t; std::cin >> t;
    
    for (int i = 0; i < t; i++) {
        testcase();
    }
}
