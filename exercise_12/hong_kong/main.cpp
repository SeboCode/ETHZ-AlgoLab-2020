#include <iostream>
#include <vector>
#include <queue>
#include <utility>
#include <CGAL/Exact_predicates_exact_constructions_kernel.h>
#include <CGAL/Delaunay_triangulation_2.h>
#include <CGAL/Triangulation_face_base_with_info_2.h>
#include <CGAL/number_utils.h>

typedef CGAL::Exact_predicates_exact_constructions_kernel K;
typedef CGAL::Triangulation_vertex_base_2<K> Vb;
typedef CGAL::Triangulation_face_base_with_info_2<K::FT,K> Fb;
typedef CGAL::Triangulation_data_structure_2<Vb,Fb> Tds;
typedef CGAL::Delaunay_triangulation_2<K,Tds> Triangulation;
typedef Triangulation::Face_handle Face_handle;
typedef K::Point_2 Point;

void testcase() {
    int n; std::cin >> n;
    int m; std::cin >> m;
    K::FT r; std::cin >> r;
    std::vector<Point> trees(n);
    
    for (int i = 0; i < n; i++) {
        long x; std::cin >> x;
        long y; std::cin >> y;
        trees[i] = Point(x, y);
    }
    
    Triangulation t(trees.begin(), trees.end());
    std::priority_queue<std::pair<K::FT, Face_handle>> queue{};
    
    for (auto face = t.all_faces_begin(); face != t.all_faces_end(); face++) {
        if (t.is_infinite(face)) {
            queue.push({CGAL::square(K::FT(std::pow(2, 50))), face});
        } else {
            // We have to use the circumcenter radius as an upper bound for the
            // maximum takeoff distance, as it could be the case that all
            // neighboring triangles have a smaller takeoff distance.
            const Point center = CGAL::circumcenter(face->vertex(0)->point(), face->vertex(1)->point(), face->vertex(2)->point());
            queue.push({CGAL::squared_distance(center, face->vertex(0)->point()), face});
        }
    }
    
    while (!queue.empty()) {
        auto pair = queue.top();
        queue.pop();
        K::FT squaredDistance = pair.first;
        Face_handle face = pair.second;
        
        if (face->info() != 0) {
            continue;
        }
        
        face->info() = squaredDistance;
        
        for (int i = 0; i < 3; i++) {
            Face_handle neighbor = face->neighbor(i);
            
            if (!t.is_infinite(neighbor) && neighbor->info() == 0) {
                K::FT minSquaredDistance = CGAL::min(squaredDistance, t.segment(face, i).squared_length());
                queue.push({minSquaredDistance, neighbor});
            }
        }
    }
    
    for (int i = 0; i < m; i++) {
        long x; std::cin >> x;
        long y; std::cin >> y;
        K::FT s; std::cin >> s;
        Point ballonLocation(x, y);
        K::FT minimumSquaredDistance = CGAL::square(r + s);
        
        if (CGAL::squared_distance(ballonLocation, t.nearest_vertex(ballonLocation)->point()) < minimumSquaredDistance) {
            std::cout << "n";
        } else {
            Face_handle triangle = t.locate(ballonLocation);
            
            if (triangle->info() < 4 * minimumSquaredDistance) {
                std::cout << "n";
            } else {
                std::cout << "y";
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
