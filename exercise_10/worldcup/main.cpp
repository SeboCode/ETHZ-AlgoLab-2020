#include <iostream>
#include <vector>
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Delaunay_triangulation_2.h>
#include <CGAL/QP_models.h>
#include <CGAL/QP_functions.h>

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef CGAL::Delaunay_triangulation_2<K> Triangulation;
typedef Triangulation::Vertex_handle Vertex_handle;
typedef K::Point_2 Point;
typedef CGAL::Gmpq IT;
typedef CGAL::Gmpq ET;
typedef CGAL::Quadratic_program<IT> Program;
typedef CGAL::Quadratic_program_solution<ET> Solution;

double floor_to_double(CGAL::Quotient<ET> const & x) {
    double a = std::floor(CGAL::to_double(x));
    while (a > x) a -= 1;
    while (a+1 <= x) a += 1;
    return a;
}

void testcase() {
    int n; std::cin >> n;
    int m; std::cin >> m;
    int c; std::cin >> c;
    std::vector<Point> locations(n + m);
    std::vector<std::vector<IT>> revenue(n, std::vector<IT>(m));
    Program lp(CGAL::SMALLER, true, 0, false, 0);
    
    for (int w = 0; w < n; w++) {
        std::cin >> locations[w];
        int s; std::cin >> s;
        int a; std::cin >> a;
        
        for (int i = 0; i < m; i++) {
            lp.set_a(w * m + i, 3 * i, 1); // Constraint for <= d
            lp.set_a(w * m + i, 3 * i + 1, -1); // Constraint for >= d
            lp.set_a(w * m + i, 3 * i + 2, a); // Constraint for <= u
            lp.set_a(w * m + i, 3 * m + w, 1); // Constraint for <= s
        }
        
        lp.set_b(3 * m + w, s);
    }
    
    for (int i = 0; i < m; i++) {
        std::cin >> locations[i + n];
        int d; std::cin >> d;
        int u; std::cin >> u;
        
        lp.set_b(3 * i, d);
        lp.set_b(3 * i + 1, -d);
        lp.set_b(3 * i + 2, u * 100);
    }
    
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            int r; std::cin >> r;
            revenue[i][j] = r;
        }
    }
    
    Triangulation t(locations.begin(), locations.end());
    
    for (int k = 0; k < c; k++) {
        Point contourCenter; std::cin >> contourCenter;
        long r; std::cin >> r;
        K::FT squaredRadius = r * r;
        
        if (CGAL::squared_distance(contourCenter, t.nearest_vertex(contourCenter)->point()) >= squaredRadius) {
            continue;
        }
        
        for (int i = 0; i < n; i++) {
            bool warehouseInCircle = CGAL::squared_distance(contourCenter, locations[i]) < squaredRadius;
            
            for (int j = 0; j < m; j++) {
                bool stadiumInCircle = CGAL::squared_distance(contourCenter, locations[j + n]) < squaredRadius;
                
                if (warehouseInCircle != stadiumInCircle) {
                    revenue[i][j] -= 0.01;
                }
            }
        }
    }
    
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            lp.set_c(i * m + j, -revenue[i][j]);
        }
    }
    
    Solution s = CGAL::solve_linear_program(lp, ET());
    
    if (s.is_infeasible()) {
        std::cout << "RIOT!" << std::endl;
    } else {
        std::cout << std::setprecision(0) << std::fixed << floor_to_double(-s.objective_value()) << std::endl;
    }
}

int main() {
    std::ios_base::sync_with_stdio(false);
    int t; std::cin >> t;
    
    for (int i = 0; i < t; i++) {
        testcase();
    }
}
