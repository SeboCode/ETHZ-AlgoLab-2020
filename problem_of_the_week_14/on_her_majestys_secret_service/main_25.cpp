#include <iostream>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/successive_shortest_path_nonnegative_weights.hpp>
#include <boost/graph/find_flow_cost.hpp>
    
typedef boost::adjacency_list_traits<boost::vecS, boost::vecS, boost::directedS> traits;
typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::directedS,
    boost::no_property, boost::property<boost::edge_capacity_t, long,
        boost::property<boost::edge_residual_capacity_t, long,
            boost::property<boost::edge_reverse_t, traits::edge_descriptor,
                boost::property<boost::edge_weight_t, long>>>>> graph_type;
typedef boost::graph_traits<graph_type>::edge_descriptor edge_desc;
typedef boost::graph_traits<graph_type>::vertex_descriptor vertex_desc;

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

void testcase() {
    int n; std::cin >> n;
    int m; std::cin >> m;
    int a; std::cin >> a;
    int s; std::cin >> s;
    int c; std::cin >> c;
    int d; std::cin >> d;
    graph_type graph(n);
    edge_adder adder(graph);
    vertex_desc const source = boost::add_vertex(graph);
    vertex_desc const target = boost::add_vertex(graph);
    
    for (int i = 0; i < m; i++) {
        char w; std::cin >> w;
        int x; std::cin >> x;
        int y; std::cin >> y;
        int z; std::cin >> z;
        adder.add_edge(x, y, a, z);
        
        if (w == 'L') {
            adder.add_edge(y, x, a, z);
        }
    }
    
    for (int i = 0; i < a; i++) {
        int p; std::cin >> p;
        adder.add_edge(source, p, 1, 0);
    }
    
    for (int i = 0; i < s; i++) {
        int p; std::cin >> p;
        adder.add_edge(p, target, c, d);
    }
    
    boost::successive_shortest_path_nonnegative_weights(graph, source, target);
    std::cout << boost::find_flow_cost(graph) << std::endl;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    int t; std::cin >> t;
    
    for (int i = 0; i < t; i++) {
        testcase();
    }
}
