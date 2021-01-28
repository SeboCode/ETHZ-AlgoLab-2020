#include <iostream>
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;

void testcase(int n) {
    long x; std::cin >> x;
    long y; std::cin >> y;
    long a; std::cin >> a;
    long b; std::cin >> b;
    K::Ray_2 ray(K::Point_2(x, y), K::Point_2(a, b));
    bool intersects = false;
    
    for (int i = 0; i < n; i++) {
        long r; std::cin >> r;
        long s; std::cin >> s;
        long t; std::cin >> t;
        long u; std::cin >> u;
        
        if (!intersects) {
            K::Segment_2 segment(K::Point_2(r, s), K::Point_2(t, u));
            
            if (CGAL::do_intersect(ray, segment)) {
                intersects = true;
            }
        }
    }
    
    if (intersects) {
        std::cout << "yes" << std::endl;
    } else {
        std::cout << "no" << std::endl;
    }
}

int main() {
    std::ios_base::sync_with_stdio(false);
    int n; std::cin >> n;
    
    while (n != 0) {
        testcase(n);
        std::cin >> n;
    }
}
