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

int max = std::pow(2, 7);

void testcase() {
    int n; std::cin >> n;
    int m; std::cin >> m;
    int l; std::cin >> l;
    graph_type graph(n);
    EdgeAdder edgeAdder(graph);
    vertex_descriptor const source = boost::add_vertex(graph);
    vertex_descriptor const target = boost::add_vertex(graph);
    // This initial (and terminal) capacity gives an upper bound on how many shortcuts we can take at a certain position.
    edgeAdder.addEdge(source, 0, l, 0);
    edgeAdder.addEdge(n-1, target, l, 0);
    
    for (int i = 0; i < n-1; i++) {
        edgeAdder.addEdge(i, i+1, l, max);
    }
    
    for (int i = 0; i < m; i++) {
        int x; std::cin >> x;
        int y; std::cin >> y;
        int q; std::cin >> q;
        // Shortcut from y to x with q less cost.
        edgeAdder.addEdge(x, y, 1, (y - x) * max - q);
    }
    
    boost::successive_shortest_path_nonnegative_weights(graph, source, target);
    // The cost without using any shortcuts is flow * max * (n - 1).
    // Flow is always exactly l, as we don't introduce any limiting factors when adding the shortcuts.
    // The difference of the cost without shortcuts and the calculated cost is maximized under the given
    // flow restriction. This difference represents a sum of q's, and since it is the maximum under the
    // given flow restrictions, this is the result we're looking for.
    std::cout << l * max * (n - 1) - boost::find_flow_cost(graph) << std::endl;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    int t; std::cin >> t;
    
    for (int i = 0; i < t; i++) {
        testcase();
    }
}
