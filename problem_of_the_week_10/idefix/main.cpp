#include <iostream>
#include <vector>
#include <utility>
#include <tuple>
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
    int m; std::cin >> m;
    K::FT s; std::cin >> s;
    int k; std::cin >> k;
    std::vector<std::pair<Point, int>> treePositions(n);
    
    for (int i = 0; i < n; i++) {
        Point position; std::cin >> position;
        treePositions[i] = {position, i};
    }
    
    Triangulation t(treePositions.begin(), treePositions.end());
    std::vector<std::tuple<K::FT, int, int>> distances{};
    
    for (Edge_iterator e = t.finite_edges_begin(); e != t.finite_edges_end(); e++) {
        int vertexIndex1 = e->first->vertex(t.ccw(e->second))->info();
        int vertexIndex2 = e->first->vertex(t.cw(e->second))->info();
        distances.push_back({t.segment(*e).squared_length(), vertexIndex1, vertexIndex2});
    }
    
    for (int i = 0; i < m; i++) {
        Point bonePosition; std::cin >> bonePosition;
        Vertex_handle nearestVertex = t.nearest_vertex(bonePosition);
        distances.push_back({CGAL::squared_distance(nearestVertex->point(), bonePosition) * 4, nearestVertex->info(), -1});
    }
    
    std::sort(distances.begin(), distances.end());
    int maxBones = 0;
    K::FT minimumRadius = -1;
    boost::disjoint_sets_with_storage<> disjoint_set(n);
    std::vector<int> boneCount(n, 0);
    
    for (auto distance : distances) {
        K::FT squaredDistance;
        int vertexIndex1;
        int vertexIndex2;
        std::tie(squaredDistance, vertexIndex1, vertexIndex2) = distance;
        
        if (vertexIndex2 != -1) {
            int v = disjoint_set.find_set(vertexIndex1);
            int u = disjoint_set.find_set(vertexIndex2);
            
            if (v != u) {
                int sum = boneCount[v] + boneCount[u];
                disjoint_set.link(v, u);
                boneCount[disjoint_set.find_set(vertexIndex1)] = sum;
            }
        } else {
            boneCount[disjoint_set.find_set(vertexIndex1)]++;
        }
        
        if (squaredDistance <= s) {
            maxBones = std::max(maxBones, boneCount[disjoint_set.find_set(vertexIndex1)]);
        }
        
        if (minimumRadius == -1 && boneCount[disjoint_set.find_set(vertexIndex1)] >= k) {
            minimumRadius = squaredDistance;
        }
    }
    
    std::cout << std::setprecision(0) << std::fixed << maxBones << ' ' << minimumRadius << std::endl;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    int t; std::cin >> t;
    
    for (int i = 0; i < t; i++) {
        testcase();
    }
}
