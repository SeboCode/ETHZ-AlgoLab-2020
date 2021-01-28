#include <iostream>
#include <vector>
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Delaunay_triangulation_2.h>
#include <CGAL/Triangulation_vertex_base_with_info_2.h>
#include <boost/pending/disjoint_sets.hpp>

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef CGAL::Triangulation_vertex_base_with_info_2<int, K> Vb;
typedef CGAL::Triangulation_face_base_2<K> Fb;
typedef CGAL::Triangulation_data_structure_2<Vb, Fb> Tds;
typedef CGAL::Delaunay_triangulation_2<K, Tds> Triangulation;
typedef Triangulation::Finite_edges_iterator Edge_iterator;
typedef Triangulation::Vertex_handle Vertex_handle;
typedef K::Point_2 Point;

K::FT maximumSquaredDistance(Triangulation const &t) {
    K::FT distance = -1;
    
    for (Edge_iterator e = t.finite_edges_begin(); e != t.finite_edges_end(); e++) {
        if (distance == -1) {
            distance = t.segment(*e).squared_length();
        } else {
            distance = CGAL::min(distance, t.segment(*e).squared_length());
        }
    }
    
    return distance;
}

int familyAmount(Triangulation const &t, long s0, int n) {
    boost::disjoint_sets_with_storage<> disjoint_set(n);
    int connectedComponentCount = n;
    
    for (Edge_iterator e = t.finite_edges_begin(); e != t.finite_edges_end(); e++) {
        if (t.segment(*e).squared_length() < s0) {
            Vertex_handle v1 = e->first->vertex((e->second + 1) % 3);
            Vertex_handle v2 = e->first->vertex((e->second + 2) % 3);
            
            if (disjoint_set.find_set(v1->info()) != disjoint_set.find_set(v2->info())) {
                disjoint_set.link(v1->info(), v2->info());
                connectedComponentCount--;
            }
        }
    }
    
    return connectedComponentCount;
}

void testcase() {
    int n; std::cin >> n;
    int k; std::cin >> k;
    int f0; std::cin >> f0;
    long s0; std::cin >> s0;
    std::vector<std::pair<Point, int>> tents{};
    
    for (int i = 0; i < n; i++) {
        int x; std::cin >> x;
        int y; std::cin >> y;
        tents.push_back({Point(x, y), i});
    }
    
    Triangulation triangulation(tents.begin(), tents.end());
    K::FT s = maximumSquaredDistance(triangulation);
    int f = familyAmount(triangulation, s0, n);
    
    std::cout << std::setprecision(0) << std::fixed << s << " " << f << std::endl;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    int t; std::cin >> t;
    
    for (int i = 0; i < t; i++) {
        testcase();
    }
}
