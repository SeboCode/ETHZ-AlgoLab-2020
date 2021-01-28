#include <iostream>
#include <CGAL/Exact_predicates_exact_constructions_kernel.h>
#include <CGAL/Min_circle_2.h>
#include <CGAL/Min_circle_2_traits_2.h>
#include <vector>

typedef CGAL::Exact_predicates_exact_constructions_kernel K;
typedef CGAL::Min_circle_2<CGAL::Min_circle_2_traits_2<K>> Min_circle;
typedef K::Point_2 Point;

double ceil_to_double(const K::FT &x) {
    double a = std::ceil(CGAL::to_double(x));
    while (a-1 >= x) {
        a -= 1;
    }
    
    while (a < x) {
        a += 1;
    }
    
    return a;
}

void testcase(int n) {
    std::vector<Point> houses(n);
    
    for (int i = 0; i < n; ++i) {
        long x; std::cin >> x;
        long y; std::cin >> y;
        houses[i] = Point(x, y);
    }
    
    Min_circle minCircle(houses.begin(), houses.end(), true);
    auto circle = minCircle.circle();
    auto squaredRadius = circle.squared_radius();
    auto center = circle.center();
    Point radiusPoint = Point(center.x(), center.y() + std::ceil(std::sqrt(CGAL::to_double(squaredRadius))));
    
    while (CGAL::squared_distance(center, Point(radiusPoint.x(), radiusPoint.y() - 1)) >= squaredRadius) {
        radiusPoint = Point(radiusPoint.x(), radiusPoint.y() - 1);
    }
    
    while (CGAL::squared_distance(center, radiusPoint) < squaredRadius) {
        radiusPoint = Point(radiusPoint.x(), radiusPoint.y() + 1);
    }
    
    std::cout << std::fixed
              << std::setprecision(0)
              << ceil_to_double(radiusPoint.y() - center.y())
              << std::endl;
}

int main(){
    std::ios_base::sync_with_stdio(false);
    int n; std::cin >> n;
    
    while (n != 0) {
        testcase(n);
        std::cin >> n;
    }
}
