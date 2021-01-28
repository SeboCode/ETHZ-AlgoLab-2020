#include <iostream>
#include <CGAL/QP_models.h>
#include <CGAL/QP_functions.h>
#include <CGAL/Gmpz.h>

typedef int IT;
typedef CGAL::Gmpz ET;
typedef CGAL::Quadratic_program<IT> Program;
typedef CGAL::Quadratic_program_solution<ET> Solution;

double floor_to_double(const CGAL::Quotient<ET> &x) {
    double a = std::floor(CGAL::to_double(x));
    
    while (a > x) {
        a -= 1;
    }
    
    while (a+1 <= x) {
        a += 1;
    }
    
    return a;
}

void testcase(int n, int m) {
    Program lp(CGAL::SMALLER, true, 0, false, 0);
    
    for (int i = 0; i < n; i++) {
        int min; std::cin >> min;
        int max; std::cin >> max;
        lp.set_b(2*i, max);
        lp.set_b(2*i+1, -min);
    }
    
    for (int i = 0; i < m; i++) {
        int p; std::cin >> p;
        
        for (int j = 0; j < n; j++) {
            int c; std::cin >> c;
            lp.set_a(i, 2*j, c);
            lp.set_a(i, 2*j+1, -c);
        }
        
        lp.set_c(i, p);
    }
    
    Solution s = CGAL::solve_linear_program(lp, ET());
    
    if (s.is_unbounded()) {
        // should never occure
        std::cout << 0 << std::endl;
    } else if (s.is_infeasible()) {
        std::cout << "No such diet." << std::endl;
    } else {
        std::cout << floor_to_double(s.objective_value()) << std::endl;
    }
}

int main() {
    std::ios_base::sync_with_stdio(false);
    
    while (true) {
        int n; std::cin >> n;
        int m; std::cin >> m;
        
        if (n == 0 && m == 0) {
            break;
        }
        
        testcase(n, m);
    }
}
