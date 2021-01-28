#include <iostream>
#include <vector>
#include <set>
#include <map>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/successive_shortest_path_nonnegative_weights.hpp>
#include <boost/graph/find_flow_cost.hpp>
#include <boost/graph/push_relabel_max_flow.hpp>

typedef boost::adjacency_list_traits<boost::vecS, boost::vecS, boost::directedS> traits;
typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::directedS, boost::no_property,
    boost::property<boost::edge_capacity_t, long,
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

struct Booking {
    int s, t, d, a, p;
};

int const MAX_T = 100000;
int const MAX_P = 100;
int const INF_CAPACITY = 1000; // MAX_S * MAX_L

void testcase() {
    int N; std::cin >> N;
    int S; std::cin >> S;
    std::vector<Booking> bookings(N);
    std::vector<int> initialCarAmount(S);
    std::vector<std::set<int>> relevantTimes(S, std::set<int>{});
    
    for (int i = 0; i < S; i++) {
        std::cin >> initialCarAmount[i];
        relevantTimes[i].insert(0);
        relevantTimes[i].insert(MAX_T);
    }
    
    for (int i = 0; i < N; i++) {
        int s; std::cin >> s; s--;
        int t; std::cin >> t; t--;
        int d; std::cin >> d;
        int a; std::cin >> a;
        int p; std::cin >> p;
        bookings[i] = {s, t, d, a, p};
        relevantTimes[s].insert(d);
        relevantTimes[t].insert(a);
    }
    
    std::vector<vertex_desc> startVertexOfStore(S+1, 0);
    // Using this and startVertexOfStore, we can calculate the vertexnumber of
    // a given store for one of its relevant times.
    std::vector<std::map<int, int>> timeToVertexOffset(S, std::map<int, int>{});
    
    for (int i = 0; i < S; i++) {
        int offset = 0;
        
        for (int t : relevantTimes[i]) {
            timeToVertexOffset[i][t] = offset;
            offset++;
        }
        
        startVertexOfStore[i+1] = startVertexOfStore[i] + offset;
    }
    
    graph_type graph(startVertexOfStore.back());
    edge_adder adder(graph);
    vertex_desc const source = boost::add_vertex(graph);
    vertex_desc const target = boost::add_vertex(graph);
    
    for (int i = 0; i < S; i++) {
        adder.add_edge(source, startVertexOfStore[i], initialCarAmount[i], 0);
        adder.add_edge(startVertexOfStore[i+1]-1, target, INF_CAPACITY, 0);
        int offset = -1;
        int previousTime = 0;
        
        for (int t : relevantTimes[i]) {
            if (offset != -1) {
                adder.add_edge(startVertexOfStore[i] + offset, startVertexOfStore[i] + offset + 1, INF_CAPACITY, MAX_P * (t - previousTime));
            }
            
            offset++;
            previousTime = t;
        }
    }
    
    for (Booking booking : bookings) {
        adder.add_edge(startVertexOfStore[booking.s] + timeToVertexOffset[booking.s][booking.d],
                        startVertexOfStore[booking.t] + timeToVertexOffset[booking.t][booking.a],
                        1, (booking.a - booking.d) * MAX_P - booking.p);
    }
    
    int flow = boost::push_relabel_max_flow(graph, source, target);
    boost::successive_shortest_path_nonnegative_weights(graph, source, target);
    // Cast necessary, as there can be an overflow if the flow gets too big.
    std::cout << (long) MAX_P * MAX_T * flow - boost::find_flow_cost(graph) << std::endl;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    int t; std::cin >> t;
    
    for (int i = 0; i < t; i++) {
        testcase();
    }
}
