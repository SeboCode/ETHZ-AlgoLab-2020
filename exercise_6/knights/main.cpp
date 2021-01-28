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
    int m; std::cin >> m;
    int n; std::cin >> n;
    int k; std::cin >> k;
    int c; std::cin >> c;
    
    if (n == 0 || m == 0) {
        std::cout << 0 << std::endl;
        return;
    }
    
    graph_type graph(2*n*m);
    EdgeAdder edgeAdder(graph);
    vertex_descriptor source = boost::add_vertex(graph);
    vertex_descriptor target = boost::add_vertex(graph);
    
    for (int i = 0; i < k; i++) {
        int x; std::cin >> x;
        int y; std::cin >> y;
        edgeAdder.addEdge(source, y * m + x, 1);
    }
    
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            int currentInTile = j * m + i;
            int currentOutTile = n * m + currentInTile;
            edgeAdder.addEdge(currentInTile, currentOutTile, c);
            
            if (i == 0 || i == m - 1) {
                edgeAdder.addEdge(currentOutTile, target, 1);
            }
            
            if (j == 0 || j == n - 1) {
                edgeAdder.addEdge(currentOutTile, target, 1);
            }
            
            if (i < m - 1) {
                int rightInTile = j * m + i + 1;
                int rightOutTile = n * m + rightInTile;
                edgeAdder.addEdge(currentOutTile, rightInTile, 1);
                edgeAdder.addEdge(rightOutTile, currentInTile, 1);
            }
            
            if (j < n - 1) {
                int downInTile = (j + 1) * m + i;
                int downOutTile = n * m + downInTile;
                edgeAdder.addEdge(currentOutTile, downInTile, 1);
                edgeAdder.addEdge(downOutTile, currentInTile, 1);
            }
        }
    }
    
    std::cout << boost::push_relabel_max_flow(graph, source, target) << std::endl;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    int t; std::cin >> t;
    
    for (int i = 0; i < t; i++) {
        testcase();
    }
}
