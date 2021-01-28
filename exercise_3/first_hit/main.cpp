#include <iostream>
#include <vector>
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Exact_predicates_exact_constructions_kernel.h>

typedef CGAL::Exact_predicates_exact_constructions_kernel K;
typedef K::Point_2 Point;
typedef K::Segment_2 Segment;
typedef K::Ray_2 Ray;

double floor_to_double(const K::FT &x) {
    double a = std::floor(CGAL::to_double(x));
    while (a > x) {
        a -= 1;
    }
    
    while (a+1 <= x) {
        a += 1;
    }
    
    return a;
}

template <typename T>
Point getPoint(const T &intersection, const Point &rayStart) {
    if (const Point* point = boost::get<Point>(&*intersection)) {
        return *point;
    } else if (const Segment* segment = boost::get<Segment>(&*intersection)) {
        if (CGAL::squared_distance(segment->source(), rayStart) <= CGAL::squared_distance(segment->target(), rayStart)) {
            return segment->source();
        } else {
            return segment->target();
        }
    } else {
        throw std::runtime_error("strange segment intersection");
    }
}

void testcase(int n) {
    long x; std::cin >> x;
    long y; std::cin >> y;
    long a; std::cin >> a;
    long b; std::cin >> b;
    Point rayStart(x, y);
    Ray ray(rayStart, Point(a, b));
    std::vector<Segment> obstacles(n);
    
    for (int i = 0; i < n; i++) {
        long r; std::cin >> r;
        long s; std::cin >> s;
        long t; std::cin >> t;
        long u; std::cin >> u;
        obstacles[i] = Segment(Point(r, s), Point(t, u));
    }
    
    // not really needed, but necessary, if the testsets have a bad input order
    std::random_shuffle(obstacles.begin(), obstacles.end());
    
    int i = 0;
    
    while (i < n) {
        if (CGAL::do_intersect(obstacles[i], ray)) {
            break;
        }
        
        i++;
    }
    
    if (i == n) {
        std::cout << "no" << std::endl;
        return;
    }
    
    Segment bestSegment(rayStart, getPoint(CGAL::intersection(obstacles[i], ray), rayStart));
    i++;
    
    while (i < n) {
        if (CGAL::do_intersect(obstacles[i], bestSegment)) {
            bestSegment = Segment(rayStart, getPoint(CGAL::intersection(obstacles[i], bestSegment), rayStart));
        }
        
        i++;
    }
    
    
    std::cout << std::fixed << std::setprecision(0) << floor_to_double(bestSegment.target().x()) << " " << floor_to_double(bestSegment.target().y()) << std::endl;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    int n; std::cin >> n;
    
    while (n != 0) {
        testcase(n);
        std::cin >> n;
    }
}
