#include <iostream>
#include <vector>
#include <limits>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/dijkstra_shortest_paths.hpp>
#include <boost/graph/max_cardinality_matching.hpp>

typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::directedS, boost::no_property,
    boost::property<boost::edge_weight_t, int>> weighted_graph_type;
typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::undirectedS> graph_type;
typedef boost::graph_traits<graph_type>::vertex_descriptor vertex_desc;

void testcase() {
    int n; std::cin >> n;
    int m; std::cin >> m;
    int a; std::cin >> a;
    int s; std::cin >> s;
    int c; std::cin >> c;
    int d; std::cin >> d;
    weighted_graph_type weighted_graph(n);
    
    for (int i = 0; i < m; i++) {
        char w; std::cin >> w;
        int x; std::cin >> x;
        int y; std::cin >> y;
        int z; std::cin >> z;
        boost::add_edge(x, y, z, weighted_graph);
        
        if (w == 'L') {
            boost::add_edge(y, x, z, weighted_graph);
        }
    }
    
    std::vector<std::vector<int>> dist_map(a, std::vector<int>(n));
    
    for (int i = 0; i < a; i++) {
        int p; std::cin >> p;
        boost::dijkstra_shortest_paths(weighted_graph, p,
            boost::distance_map(boost::make_iterator_property_map(dist_map[i].begin(),
                boost::get(boost::vertex_index, weighted_graph))));
    }
    
    std::vector<std::vector<int>> shelterDistances(a, std::vector<int>(s));
    
    for (int i = 0; i < s; i++) {
        int p; std::cin >> p;
        
        for (int j = 0; j < a; j++) {
            shelterDistances[j][i] = dist_map[j][p];
        }
    }
    
    int left = 0;
    int right = std::numeric_limits<int>::max();
    
    while (left < right) {
        int middle = (right + left) / 2;
        graph_type graph(a + c * s);
        
        for (int i = 0; i < a; i++) {
            for (int j = 0; j < s; j++) {
                // Dijkstra stores INT_MAX in the distance map, if there is no
                // connection between the two points. Therefore, this can lead
                // to an overflow.
                if (shelterDistances[i][j] + d <= 0) {
                    continue;
                }
                
                for (int k = 0; k < c; k++) {
                    if (shelterDistances[i][j] + (k+1) * d <= middle) {
                        boost::add_edge(i, a + k * s + j, graph);
                    }
                }
            }
        }
        
        std::vector<vertex_desc> mate_map(a + c * s);
        boost::edmonds_maximum_cardinality_matching(graph,
            boost::make_iterator_property_map(mate_map.begin(),
                boost::get(boost::vertex_index, graph)));
        int matching_size = boost::matching_size(graph,
            boost::make_iterator_property_map(mate_map.begin(),
                boost::get(boost::vertex_index, graph)));
        
        if (matching_size == a) { // In this case, all the agents make it in time.
            right = middle;
        } else { // In this case, at least one agent doesn't make it in time.
            left = middle + 1;
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
