#include <iostream>
#include <vector>
#include <utility>
#include <queue>
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Delaunay_triangulation_2.h>
#include <CGAL/Triangulation_vertex_base_with_info_2.h>

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef CGAL::Triangulation_vertex_base_with_info_2<bool,K> Vb;
typedef CGAL::Triangulation_face_base_2<K> Fb;
typedef CGAL::Triangulation_data_structure_2<Vb,Fb> Tds;
typedef CGAL::Delaunay_triangulation_2<K,Tds> Triangulation;
typedef Triangulation::Vertex_iterator Vertex_iterator;
typedef Triangulation::Vertex_handle Vertex_handle;
typedef Triangulation::Vertex_circulator Vertex_circulator;
typedef K::Point_2 Point;

int max_connected_component_size(std::vector<std::pair<Point, bool>> const & planets, int occupied, K::FT const & squaredTravelDistance) {
    Triangulation t(planets.cbegin() + occupied, planets.cend());
    int maxConnectedComponentSize = 0;
    
    for (Vertex_iterator v = t.finite_vertices_begin(); v != t.finite_vertices_end(); v++) {
        if (v->info()) {
            continue;
        }
        
        int componentSize = 1;
        std::queue<Vertex_handle> queue{};
        v->info() = true;
        queue.push(v);
        
        while (!queue.empty()) {
            Vertex_handle vertex = queue.front();
            queue.pop();
            Vertex_circulator c = t.incident_vertices(vertex);
            
            if (c != 0) {
                do {
                    if (!t.is_infinite(c) && !c->info() && CGAL::squared_distance(c->point(), vertex->point()) <= squaredTravelDistance) {
                        c->info() = true;
                        queue.push(c);
                        componentSize++;
                    }
                } while (++c != t.incident_vertices(vertex));
            }
        }
        
        maxConnectedComponentSize = std::max(maxConnectedComponentSize, componentSize);
    }
    
    return maxConnectedComponentSize;
}

void testcase() {
    int n; std::cin >> n;
    K::FT r; std::cin >> r;
    K::FT squaredTravelDistance = r * r;
    std::vector<std::pair<Point, bool>> planets(n);
    
    for (int i = 0; i < n; i++) {
        int x; std::cin >> x;
        int y; std::cin >> y;
        planets[i] = {Point(x, y), false};
    }
    
    int k = 0;
    int left = 0;
    int right = n/2 + 1;
    
    while (left < right) {
        int occupied = (right + left) / 2;
        int maxConnectedComponentSize = max_connected_component_size(planets, occupied, squaredTravelDistance);
        
        if (occupied < maxConnectedComponentSize) {
            // In this case we can recruit more planets than the emperor can take over.
            // Thus, we get a lower bound on the amount of planets we can recruit.
            k = std::max(k, occupied);
            left = occupied+1;
        } else {
            // In this case we can recruit less planets than the emperor can take over or exactly as much.
            // Regardless, we get an upper bound on the amount of planets we can recruit.
            k = std::max(k, maxConnectedComponentSize);
            right = occupied;
        }
    }
    
    std::cout << k << std::endl;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    int t; std::cin >> t;
    
    for (int i = 0; i < t; i++) {
        testcase();
    }
}
