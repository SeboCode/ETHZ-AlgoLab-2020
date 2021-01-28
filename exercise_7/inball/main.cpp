#include <iostream>
#include <CGAL/QP_models.h>
#include <CGAL/QP_functions.h>
#include <CGAL/Gmpz.h>
#include <cmath>

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

void testcase(int n) {
    int d; std::cin >> d;
    Program lp(CGAL::SMALLER, false, 0, false, 0);
    int R = d;
    
    for (int i = 0; i < n; i++) {
        int squaredSum = 0;
        
        for (int j = 0; j < d; j++) {
            int a; std::cin >> a;
            lp.set_a(j, i, a);
            squaredSum += std::pow(a, 2);
        }
        
        lp.set_a(R, i, std::sqrt(squaredSum));
        int b; std::cin >> b;
        lp.set_b(i, b);
    }
    
    lp.set_l(R, true, 0);
    lp.set_c(R, -1);
    Solution s = CGAL::solve_linear_program(lp, ET());
    
    if (s.is_unbounded()) {
        std::cout << "inf" << std::endl;
    } else if (s.is_infeasible()) {
        std::cout << "none" << std::endl;
    } else {
        std::cout << floor_to_double(-s.objective_value()) << std::endl;
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
