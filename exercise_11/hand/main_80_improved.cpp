#include <iostream>
#include <vector>
#include <tuple>
#include <algorithm>
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

void testcase() {
    int n; std::cin >> n;
    int k; std::cin >> k; // Always 1 in this solution
    int f_0; std::cin >> f_0;
    long s_0; std::cin >> s_0;
    std::vector<std::pair<Point, int>> tents(n);
    
    for (int i = 0; i < n; i++) {
        int x; std::cin >> x;
        int y; std::cin >> y;
        tents[i] = {Point(x, y), i};
    }
    
    Triangulation t(tents.begin(), tents.end());
    std::vector<std::tuple<K::FT, int, int>> edges{};
    
    for (Edge_iterator edge = t.finite_edges_begin(); edge != t.finite_edges_end(); edge++) {
        Vertex_handle v1 = edge->first->vertex(t.cw(edge->second));
        Vertex_handle v2 = edge->first->vertex(t.ccw(edge->second));
        edges.push_back({t.segment(*edge).squared_length(), v1->info(), v2->info()});
    }
    
    std::sort(edges.begin(), edges.end());
    boost::disjoint_sets_with_storage<> disjoint_set(n);
    int componentCount = n;
    std::pair<K::FT, int> solution = {0, n}; // s, f
    
    for (int i = 0; i < edges.size(); i++) {
        int v1 = std::get<1>(edges[i]);
        int v2 = std::get<2>(edges[i]);
        
        if (disjoint_set.find_set(v1) != disjoint_set.find_set(v2)) {
            // Every time we union two clusters where their distance is smaller
            // than s_0, we have one less family we can occupy, when we require
            // the distance between two families to be at least s_0.
            if (std::get<0>(edges[i]) < s_0) {
                solution.second--;
            }
            
            // As soon as we have the exact same amount of clusters as we have
            // in f_0, we want to search for the next edge that would unify two
            // clusters. The distance between these two points marks the min
            // distance between all families. This holds, as the edges are
            // sorted by their distance.
            // We have to perform this check BEFORE the componentCount
            // reduction, since we are looking for the NEXT smallest distance
            // of two clusters, AFTER we have built exactly f_0 clusters.
            if (componentCount == f_0) {
                solution.first = std::get<0>(edges[i]);
            }
          
            disjoint_set.union_set(v1, v2);
            componentCount--;
        }
    }
    
    std::cout << std::setprecision(0) << std::fixed << solution.first << " " << solution.second << std::endl;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    int t; std::cin >> t;
    
    for (int i = 0; i < t; i++) {
        testcase();
    }
}
