#include <iostream>
#include <vector>
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Delaunay_triangulation_2.h>

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef CGAL::Delaunay_triangulation_2<K> Triangulation;
typedef Triangulation::Finite_vertices_iterator Vertex_iterator;
typedef K::Point_2 Point;

double time_to_squared_distance(double time) {
    double distance = time * time + 0.5;
    return distance * distance;
}

double calculate_time(K::FT squaredDistanceFT) {
    double squaredDistance = CGAL::to_double(squaredDistanceFT);
    double time = std::ceil(std::sqrt(std::sqrt(squaredDistance) - 0.5));
    
    while (time_to_squared_distance(time) < squaredDistanceFT) {
        time += 1;
    }
    
    while (time - 1 >= 0 && time_to_squared_distance(time - 1) >= squaredDistanceFT) {
        time -= 1;
    }
    
    return time;
}

void testcase(int n) {
    int l; std::cin >> l;
    int b; std::cin >> b;
    int r; std::cin >> r;
    int t; std::cin >> t;
    std::vector<Point> bacteriaLocations(n);
    
    for (int i = 0; i < n; i++) {
        int x; std::cin >> x;
        int y; std::cin >> y;
        bacteriaLocations[i] = Point(x, y);
    }
    
    Triangulation triangulation;
    triangulation.insert(bacteriaLocations.begin(), bacteriaLocations.end());
    std::vector<K::FT> colisionRadius(n);
    int i = 0;
    
    for (Vertex_iterator v = triangulation.finite_vertices_begin(); v != triangulation.finite_vertices_end(); v++) {
        Point currentPoint = v->point();
        colisionRadius[i] = std::pow(currentPoint.x() - l, 2);
        colisionRadius[i] = CGAL::min(colisionRadius[i], std::pow(currentPoint.y() - b, 2));
        colisionRadius[i] = CGAL::min(colisionRadius[i], std::pow(r - currentPoint.x(), 2));
        colisionRadius[i] = CGAL::min(colisionRadius[i], std::pow(t - currentPoint.y(), 2));
        Triangulation::Vertex_circulator c = triangulation.incident_vertices(v);
        
        // in case we only have one vertex
        if (c != 0) {
            do {
                if (!triangulation.is_infinite(c)) {
                    colisionRadius[i] = CGAL::min(colisionRadius[i], CGAL::squared_distance(c->point(), currentPoint)/4);
                }
            } while (++c != triangulation.incident_vertices(v));
        }
        
        i++;
    }
    
    std::sort(colisionRadius.begin(), colisionRadius.end());
    std::cout << calculate_time(colisionRadius[0]) << ' '
              << calculate_time(colisionRadius[n/2]) << ' '
              << calculate_time(colisionRadius[n-1]) << std::endl;
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
