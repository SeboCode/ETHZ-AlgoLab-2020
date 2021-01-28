#include <iostream>
#include <vector>
#include <tuple>
#include <CGAL/QP_models.h>
#include <CGAL/QP_functions.h>
#include <CGAL/Gmpz.h>

typedef CGAL::Gmpz IT;
typedef CGAL::Gmpz ET;
typedef CGAL::Quadratic_program<IT> Program;
typedef CGAL::Quadratic_program_solution<ET> Solution;
typedef std::tuple<int, int, int> Location;
typedef std::tuple<CGAL::Gmpz, CGAL::Gmpz, CGAL::Gmpz> Product;

void testcase() {
    int h; std::cin >> h;
    int t; std::cin >> t;
    int degreeBound = 31;
    std::vector<Location> cells(h + t);
    
    for (int i = 0; i < h + t; i++) {
        int x; std::cin >> x;
        int y; std::cin >> y;
        int z; std::cin >> z;
        cells[i] = {x, y, z};
    }
    
    int D = 0; // Variable denoting the minimum distance of our values from the polynomial.
    std::vector<std::vector<Product>> products(degreeBound, std::vector<Product>(h + t));
    CGAL::Quadratic_program_options options;
    options.set_pricing_strategy(CGAL::QP_BLAND);
    
    for (int d = 0; d < degreeBound; d++) {
        Program lp(CGAL::SMALLER, false, 0, false, 0);
        lp.set_l(D, true, 0); // The minimum distance needs to be positive.
        lp.set_c(D, -1);
        
        for (int i = 0; i < h+t; i++) {
            int signum = i < h ? -1 : 1;
            
            if (d == 0) {
                products[d][i] = {1, 1, 1};
            } else {
                CGAL::Gmpz nextX = std::get<0>(products[d-1][i]) * std::get<0>(cells[i]);
                CGAL::Gmpz nextY = std::get<1>(products[d-1][i]) * std::get<1>(cells[i]);
                CGAL::Gmpz nextZ = std::get<2>(products[d-1][i]) * std::get<2>(cells[i]);
                products[d][i] = {nextX, nextY, nextZ};
            }
            
            lp.set_a(D, i, 1);
            int variableCounter = 1;
            
            for (int a = 0; a <= d; a++) {
                for (int b = 0; b <= d-a; b++) {
                    for (int c = 0; c <= d-a-b; c++) {
                        lp.set_a(variableCounter++, i, std::get<0>(products[a][i]) * std::get<1>(products[b][i]) * std::get<2>(products[c][i]) * signum);
                    }
                }
            }
        }
        
        Solution s = CGAL::solve_linear_program(lp, ET(), options);
        
        // We need an objective value that is either unbounded or strictly greater than 0.
        // The only problem is that we cannot creat strict bounds in an lp.
        // Thus we argue that in case our lp is feasible and its value bounded, it cannot be 0.
        // If it is unbounded, then we can trivially say that the lp has a value strictly greater than 0.
        if (!s.is_infeasible() && (s.is_unbounded() || s.objective_value() != 0)) {
            std::cout << d << std::endl;
            return;
        }
    }
    
    std::cout << "Impossible!" << std::endl;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    int N; std::cin >> N;
    
    for (int i = 0; i < N; i++) {
        testcase();
    }
}
