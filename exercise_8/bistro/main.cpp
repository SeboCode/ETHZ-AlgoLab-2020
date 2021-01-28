#include <iostream>
#include <vector>
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Delaunay_triangulation_2.h>

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef CGAL::Delaunay_triangulation_2<K> Triangulation;
typedef K::Point_2 Point;

void testcase(int n) {
    std::vector<Point> points(n);
    
    for (int i = 0; i < n; i++) {
        int x; std::cin >> x;
        int y; std::cin >> y;
        points[i] = Point(x, y);
    }
    
    Triangulation t;
    t.insert(points.begin(), points.end());
    int m; std::cin >> m;
    
    for (int i = 0; i < m; i++) {
        int x; std::cin >> x;
        int y; std::cin >> y;
        Point newLocation = Point(x, y);
        Point closest = t.nearest_vertex(newLocation)->point();
        std::cout << std::setprecision(0) << std::fixed << CGAL::squared_distance(newLocation, closest) << std::endl;
    }
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
