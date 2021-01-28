#include <iostream>
#include <vector>
#include <queue>
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Delaunay_triangulation_2.h>
#include <CGAL/Triangulation_vertex_base_with_info_2.h>

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef CGAL::Triangulation_vertex_base_with_info_2<int, K> Vb;
typedef CGAL::Triangulation_face_base_2<K> Fb;
typedef CGAL::Triangulation_data_structure_2<Vb, Fb> Tds;
typedef CGAL::Delaunay_triangulation_2<K, Tds> Triangulation;
typedef Triangulation::Finite_vertices_iterator Vertex_iterator;
typedef Triangulation::Vertex_handle Vertex_handle;
typedef K::Point_2 Point;

void testcase() {
    int n; std::cin >> n;
    int m; std::cin >> m;
    K::FT s; std::cin >> s;
    int k; std::cin >> k;
    std::vector<Point> treePositions(n);
    std::vector<Point> bonePositions(m);
    
    for (int i = 0; i < n; i++) {
        std::cin >> treePositions[i];
    }
    
    for (int i = 0; i < m; i++) {
        std::cin >> bonePositions[i];
    }
    
    Triangulation t;
    t.insert(treePositions.begin(), treePositions.end());
    
    for (Vertex_iterator v = t.finite_vertices_begin(); v != t.finite_vertices_end(); v++) {
        v->info() = -1;
    }
    
    int groupCount = 0;
    std::queue<Vertex_handle> queue{};
    
    for (Vertex_iterator v = t.finite_vertices_begin(); v != t.finite_vertices_end(); v++) {
        if (v->info() == -1) {
            queue.push(v);
            v->info() = groupCount;
            
            while (!queue.empty()) {
                Vertex_handle vertex = queue.front();
                queue.pop();
                Triangulation::Vertex_circulator c = t.incident_vertices(vertex);
                
                if (c != 0) {
                    do {
                        if (!t.is_infinite(c) && c->info() == -1 && CGAL::squared_distance(c->point(), vertex->point()) <= s) {
                            c->info() = groupCount;
                            queue.push(c);
                        }
                    } while (++c != t.incident_vertices(vertex));
                }
            }
            
            groupCount++;
        }
    }
    
    std::vector<int> boneCountInGroup(groupCount, 0);
    int maxBones = 0;
    
    for (int i = 0; i < m; i++) {
        Point bonePosition = bonePositions[i];
        Vertex_handle nearestVertex = t.nearest_vertex(bonePosition);
        
        if (CGAL::squared_distance(nearestVertex->point(), bonePosition) * 4 <= s) {
            int group = nearestVertex->info();
            boneCountInGroup[group]++;
            maxBones = std::max(maxBones, boneCountInGroup[group]);
        }
    }
    
    std::cout << std::setprecision(0) << std::fixed << maxBones << ' ' << 4 * s << std::endl;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    int t; std::cin >> t;
    
    for (int i = 0; i < t; i++) {
        testcase();
    }
}
