#include <iostream>
#include <CGAL/Exact_predicates_exact_constructions_kernel.h>
#include <CGAL/Exact_predicates_exact_constructions_kernel_with_sqrt.h>
#include <CGAL/Min_circle_2.h>
#include <CGAL/Min_circle_2_traits_2.h>
#include <vector>

typedef CGAL::Exact_predicates_exact_constructions_kernel K;
typedef CGAL::Min_circle_2<CGAL::Min_circle_2_traits_2<K>> Min_circle;
typedef K::Point_2 Point;
typedef CGAL::Exact_predicates_exact_constructions_kernel_with_sqrt WK;
typedef CGAL::Min_circle_2<CGAL::Min_circle_2_traits_2<WK>> Min_circle_wk;
typedef WK::Point_2 Point_wk;

double ceil_to_double(const WK::FT &x) {
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
    std::vector<Point_wk> importantPoints{};
    
    for (auto it = minCircle.support_points_begin(); it != minCircle.support_points_end(); it++) {
        importantPoints.push_back(Point_wk(CGAL::to_double(it->x()), CGAL::to_double(it->y())));
    }
    
    auto center = Min_circle_wk(importantPoints.begin(), importantPoints.end(), true).circle();
    std::cout << std::fixed
              << std::setprecision(0)
              << ceil_to_double(CGAL::sqrt(center.squared_radius()))
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
