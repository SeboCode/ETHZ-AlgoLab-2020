#include <iostream>
#include <vector>
#include <queue>
#include <utility>
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Delaunay_triangulation_2.h>
#include <CGAL/Triangulation_vertex_base_with_info_2.h>

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef CGAL::Triangulation_vertex_base_with_info_2<std::pair<int, bool>, K> Vb;
typedef CGAL::Triangulation_face_base_2<K> Fb;
typedef CGAL::Triangulation_data_structure_2<Vb, Fb> Tds;
typedef CGAL::Delaunay_triangulation_2<K, Tds> Triangulation;
typedef Triangulation::Finite_vertices_iterator Vertex_iterator;
typedef Triangulation::Finite_edges_iterator Edge_iterator;
typedef Triangulation::Vertex_handle Vertex_handle;
typedef K::Point_2 Point;

bool hasInterference(Triangulation const &t, K::FT const &r) {
    for (Edge_iterator e = t.finite_edges_begin(); e != t.finite_edges_end(); e++) {
        if (t.segment(*e).squared_length() <= r * r) {
            return true;
        }
    }
    
    return false;
}

bool computeComponents(Triangulation &t, K::FT const &r) {
    int componentNumber = 0;
    std::queue<Vertex_handle> queue{};
    std::vector<Point> t1{};
    std::vector<Point> t2{};
    
    for (Vertex_iterator v = t.finite_vertices_begin(); v != t.finite_vertices_end(); v++) {
        if (v->info().first == -1) {
            queue.push(v);
            v->info() = {componentNumber, false};
            
            while (!queue.empty()) {
                Vertex_handle vertex = queue.front();
                queue.pop();
                Triangulation::Vertex_circulator c = t.incident_vertices(vertex);
                
                if (c != 0) {
                    do {
                        if (!t.is_infinite(c) && CGAL::squared_distance(c->point(), vertex->point()) <= r * r) {
                            if (c->info().first == -1) {
                                c->info() = {componentNumber, !vertex->info().second};
                                queue.push(c);
                            } else {
                                if (vertex->info().second == c->info().second) {
                                    return true;
                                }
                            }
                        }
                    } while (++c != t.incident_vertices(vertex));
                }
            }
        }
        
        if (v->info().second) {
            t1.push_back(v->point());
        } else {
            t2.push_back(v->point());
        }
        
        componentNumber++;
    }
    
    return hasInterference(Triangulation(t1.begin(), t1.end()), r) || hasInterference(Triangulation(t2.begin(), t2.end()), r);
}

void testcase() {
    int n; std::cin >> n;
    int m; std::cin >> m;
    K::FT r; std::cin >> r;
    std::vector<std::pair<Point, std::pair<int, bool>>> stationPositions(n);
    
    for (int i = 0; i < n; i++) {
        Point position; std::cin >> position;
        stationPositions[i] = {position, {-1, false}};
    }
    
    Triangulation t(stationPositions.begin(), stationPositions.end());
    bool hasInterference = computeComponents(t, r);
    
    for (int i = 0; i < m; i++) {
        Point holmes; std::cin >> holmes;
        Point watson; std::cin >> watson;
        
        if (hasInterference) {
            std::cout << 'n';
        } else if (CGAL::squared_distance(holmes, watson) <= r * r) {
            std::cout << 'y';
        } else {
            Vertex_handle nearestVertexHolmes = t.nearest_vertex(holmes);
            Vertex_handle nearestVertexWatson = t.nearest_vertex(watson);
            
            if (nearestVertexHolmes->info().first == nearestVertexWatson->info().first
                && CGAL::squared_distance(holmes, nearestVertexHolmes->point()) <= r * r
                && CGAL::squared_distance(watson, nearestVertexWatson->point()) <= r * r) {
                std::cout << 'y';
            } else {
                std::cout << 'n';
            }
        }
    }
    
    std::cout << std::endl;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    int t; std::cin >> t;
    
    for (int i = 0; i < t; i++) {
        testcase();
    }
}
