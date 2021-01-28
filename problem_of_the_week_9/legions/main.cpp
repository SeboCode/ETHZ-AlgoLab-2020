#include <iostream>
#include <cmath>
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

void testcase() {
    int x; std::cin >> x;
    int y; std::cin >> y;
    int n; std::cin >> n;
    
    Program lp(CGAL::SMALLER, false, 0, false, 0);
    const int T = 0;
    const int X = 1;
    const int Y = 2;
    
    for (int i = 0; i < n; i++) {
        long a; std::cin >> a;
        long b; std::cin >> b;
        long c; std::cin >> c;
        long v; std::cin >> v;
        int sign = a * x + b * y + c < 0 ? -1 : 1;
        lp.set_a(T, i, v * std::sqrt(std::pow(a, 2) + std::pow(b, 2)));
        lp.set_a(X, i, sign * -a);
        lp.set_a(Y, i, sign * -b);
        lp.set_b(i, sign * c);
    }
    
    lp.set_l(T, true, 0);
    lp.set_c(T, -1);
    Solution s = CGAL::solve_linear_program(lp, ET());
    
    if (s.is_unbounded()) {
        // should never occure
        std::cout << "unb" << std::endl;
    } else if (s.is_infeasible()) {
        // should never occure
        std::cout << "inf" << std::endl;
    } else {
        std::cout << floor_to_double(-s.objective_value()) << std::endl;
    }
}

int main() {
    std::ios_base::sync_with_stdio(false);
    int t; std::cin >> t;
    
    for (int i = 0; i < t; i++) {
        testcase();
    }
}
