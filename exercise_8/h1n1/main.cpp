#include <iostream>
#include <vector>
#include <queue>
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Delaunay_triangulation_2.h>
#include <CGAL/Triangulation_face_base_with_info_2.h>

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef CGAL::Triangulation_vertex_base_2<K> Vb;
typedef CGAL::Triangulation_face_base_with_info_2<K::FT, K> Fb;
typedef CGAL::Triangulation_data_structure_2<Vb, Fb> Tds;
typedef CGAL::Delaunay_triangulation_2<K, Tds> Triangulation;
typedef Triangulation::Face_handle Face_handle;
typedef Triangulation::Edge Edge;
typedef K::Point_2 Point;

void testcase(int n) {
    std::vector<Point> infectedLocations(n);
    
    for (int i = 0; i < n; i++) {
        std::cin >> infectedLocations[i];
    }
    
    Triangulation t;
    t.insert(infectedLocations.begin(), infectedLocations.end());
    std::priority_queue<std::pair<K::FT, Face_handle>> queue{};
    
    for (Face_handle face = t.all_faces_begin(); face != t.all_faces_end(); face++) {
        if (t.is_infinite(face)) {
            for (int j = 0; j < 3; j++) {
                Face_handle neighborFace = face->neighbor(j);
                
                if (!t.is_infinite(neighborFace)) {
                    queue.push({t.segment(Edge(face, j)).squared_length() / 4, neighborFace});
                }
            }
        } else {
            face->info() = -1;
            queue.push({-1, face});
        }
    }
    
    while (!queue.empty()) {
        K::FT escapeSize;
        Face_handle face;
        std::tie(escapeSize, face) = queue.top();
        queue.pop();
        
        if (face->info() == -1) {
            face->info() = escapeSize;
        }
        
        for (int j = 0; j < 3; j++) {
            Face_handle neighborFace = face->neighbor(j);
            
            if (!t.is_infinite(neighborFace) && neighborFace->info() == -1) {
                K::FT updatedEscapeSize = CGAL::min(t.segment(Edge(face, j)).squared_length() / 4, escapeSize);
                queue.push({updatedEscapeSize, neighborFace});
            }
        }
    }
    
    int m; std::cin >> m;
    
    for (int i = 0; i < m; i++) {
        Point point; std::cin >> point;
        long d; std::cin >> d;
        
        Face_handle face = t.locate(point);
        
        if (CGAL::squared_distance(t.nearest_vertex(point)->point(), point) < d || (!t.is_infinite(face) && face->info() < d)) {
            std::cout << "n";
        } else {
            std::cout << "y";
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
