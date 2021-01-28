#include <iostream>
#include <vector>
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Delaunay_triangulation_2.h>
#include <CGAL/Triangulation_face_base_with_info_2.h>

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef CGAL::Triangulation_vertex_base_2<K> Vb;
typedef CGAL::Triangulation_face_base_with_info_2<int, K> Fb;
typedef CGAL::Triangulation_data_structure_2<Vb, Fb> Tds;
typedef CGAL::Delaunay_triangulation_2<K, Tds> Triangulation;
typedef Triangulation::Face_handle Face_handle;
typedef Triangulation::Edge Edge;
typedef K::Point_2 Point;

bool dfs(Triangulation &t, Face_handle &face, long d, int i) {
    if (t.is_infinite(face)) {
        return true;
    }
    
    for (int j = 0; j < 3; j++) {
        Face_handle neighborFace = face->neighbor(j);
        
        if (neighborFace->info() != i && t.segment(Edge(face, j)).squared_length() / 4 >= d) {
            neighborFace->info() = i;
            
            if (dfs(t, neighborFace, d, i)) {
                return true;
            }
        }
    }
    
    return false;
}

void testcase(int n) {
    std::vector<Point> infectedLocations(n);
    
    for (int i = 0; i < n; i++) {
        std::cin >> infectedLocations[i];
    }
    
    Triangulation t;
    t.insert(infectedLocations.begin(), infectedLocations.end());
    int m; std::cin >> m;
    
    for (int i = 0; i < m; i++) {
        Point point; std::cin >> point;
        long d; std::cin >> d;
        
        Face_handle face = t.locate(point);
        
        if (CGAL::squared_distance(t.nearest_vertex(point)->point(), point) < d) {
            std::cout << "n";
            continue;
        }
        
        face->info() = i;
        
        if (dfs(t, face, d, i)) {
            std::cout << "y";
        } else {
            std::cout << "n";
        }
    }
    
    std::cout << std::endl;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    
    while (true) {
        int n; std::cin >> n;
        
        if (n == 0) {
            break;
        }
        
        testcase(n);
    }
}
