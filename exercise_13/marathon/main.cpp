#include <iostream>
#include <limits>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/push_relabel_max_flow.hpp>
#include <boost/graph/successive_shortest_path_nonnegative_weights.hpp>
#include <boost/graph/find_flow_cost.hpp>
#include <boost/graph/dijkstra_shortest_paths.hpp>

typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::undirectedS,
    boost::no_property, boost::property<boost::edge_weight_t, int>> distance_graph;
    
typedef boost::adjacency_list_traits<boost::vecS, boost::vecS, boost::directedS> traits;
typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::directedS,
    boost::no_property, boost::property<boost::edge_capacity_t, long,
        boost::property<boost::edge_residual_capacity_t, long,
            boost::property<boost::edge_reverse_t, traits::edge_descriptor,
                boost::property<boost::edge_weight_t, long>>>>> flow_graph;
typedef boost::graph_traits<flow_graph>::edge_descriptor edge_desc;
typedef boost::graph_traits<flow_graph>::vertex_descriptor vertex_desc;

class edge_adder {
    flow_graph &G;
    
    public:
        explicit edge_adder(flow_graph &G) : G(G) {}
        
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

void reset_source_edge(edge_desc const & e, edge_desc const & rev_e, long capacity, flow_graph & graph) {
    auto c_map = boost::get(boost::edge_capacity, graph);
    auto r_map = boost::get(boost::edge_reverse, graph);
    auto w_map = boost::get(boost::edge_weight, graph);
    c_map[e] = capacity;
    c_map[rev_e] = 0;
    r_map[e] = rev_e;
    r_map[rev_e] = e;
    w_map[e] = 0;
    w_map[rev_e] = 0;
}

void testcase() {
    int n; std::cin >> n;
    int m; std::cin >> m;
    int s; std::cin >> s;
    int f; std::cin >> f;
    distance_graph dGraph(n);
    flow_graph fGraph(n);
    edge_adder adder(fGraph);
    vertex_desc const source = boost::add_vertex(fGraph);
    edge_desc const source_edge = boost::add_edge(source, s, fGraph).first;
    edge_desc const source_rev_edge = boost::add_edge(s, source, fGraph).first;
    reset_source_edge(source_edge, source_rev_edge, 0, fGraph);
    
    for (int i = 0; i < m; i++) {
        int a; std::cin >> a;
        int b; std::cin >> b;
        int c; std::cin >> c;
        int d; std::cin >> d;
        boost::add_edge(a, b, d, dGraph);
        adder.add_edge(a, b, c, d);
        adder.add_edge(b, a, c, d);
    }
    
    std::vector<int> dist_map(n);
    boost::dijkstra_shortest_paths(dGraph, s,
        boost::distance_map(boost::make_iterator_property_map(dist_map.begin(),
            boost::get(boost::vertex_index, dGraph))));
    int distance = dist_map[f];
    int left = 0;
    int right = boost::push_relabel_max_flow(fGraph, s, f);
    
    while (left < right) {
        // The +1 is needed, because left+1 = right is possible. In this config,
        // we always end up with left = middle (as the fraction is rounded
        // towards 0) and thus we end in an endless loop. With the +1 we
        // guarantee that left != middle in each iteration.
        int middle = (right + left + 1) / 2;
        reset_source_edge(source_edge, source_rev_edge, middle, fGraph);
        boost::successive_shortest_path_nonnegative_weights(fGraph, source, f);
        int cost = boost::find_flow_cost(fGraph);
        
        // In this case we have a potential bottleneck of the flow.
        // We need to set left to middle, as left contains the result and it
        // could be the case that middle+1 already gets bottlenecked by a
        // capacity of the graph.
        if (middle * distance == cost) {
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
