#include <iostream>
#include <CGAL/QP_models.h>
#include <CGAL/QP_functions.h>
#include <CGAL/Gmpz.h>

// Long is needed, as the constraint for Tywin could have coefficients of a
// larger size than int can handle.
typedef long IT;
typedef CGAL::Gmpz ET;
typedef CGAL::Quadratic_program<IT> Program;
typedef CGAL::Quadratic_program_solution<ET> Solution;

double ceil_to_double(const CGAL::Quotient<ET>& x) {
    double a = std::ceil(CGAL::to_double(x));
    while (a-1 >= x) a -= 1;
    while (a < x) a += 1;
    return a;
}

void testcase() {
    int n; std::cin >> n;
    int m; std::cin >> m;
    long s; std::cin >> s;
    Program lp (CGAL::SMALLER, false, 0, false, 0);
    int const a = 0;
    int const b = 1;
    int const c = 2;
    int const l = 3; // Length of the longest fresh water pipe.
    long xs = 0;
    long ys = 0;
    long bs = 0;
    
    // We define the sewer line to be:       x + a_s y + b = 0
    // We define the fresh water line to be: a_w x + y + c = 0
    // The reason we need a guaranteed x portion in the sewer line so it is non-horizontal.
    // The reason we need a guaranteed y portion in the frehs water line so it is non-vertical.
    //
    // The normal vector of the sewer line is (1, a_s).
    // The normal vector of the sewer line is (a_w, 1).
    // As such, we get the scalar product of (1, a_s) * (a_w, 1) = a_w + a_s.
    // For the two lines to be orthogonal, the scalar product of their normal
    // vectors needs to be 0. Thus we have a_w = -a and a_s = a for some a.
    
    for (int i = 0; i < n; i++) {
        int x; std::cin >> x;
        int y; std::cin >> y;
        
        // Nobelhouse needs to be on the left of the sewerpipe.
        // => Sewerpipe needs to be on the right of the house.
        // => x + ay + b <= 0
        // <=> ay + b <= -x
        lp.set_a(a, i, y);
        lp.set_a(b, i, 1);
        lp.set_b(i, -x);
        
        // Let x_l be the x-position of the sewerpipe on the same height as the house.
        // Let x_h be the x-position of the house itself.
        // We know that the house is on the left of the sewerpipe, thus we want
        // to know the value x_2 - x_1 and sum that up for all nobelhouses.
        // x_2 + ay + b = 0
        // <=> x_2 = -ay - b
        // => One portion of the sum is -ay - 1*b - x_1
        ys += -y;
        bs += -1;
        xs += -x;
        
        int const nobel_freshwater_index_under = n + m + 2 * i;
        int const nobel_freshwater_index_over = nobel_freshwater_index_under + 1;
        
        // -ax + y + c <= 0
        // The left hand side is the point of the line that is above the house.
        // We thus need to remove l to get to the position of the house.
        // => -ax + c - l <= -y
        lp.set_a(a, nobel_freshwater_index_under, -x);
        lp.set_a(c, nobel_freshwater_index_under, 1);
        lp.set_a(l, nobel_freshwater_index_under, -1);
        lp.set_b(nobel_freshwater_index_under, -y);
        
        // -ax + y + c >= 0
        // The left hand side is the point of the line that is below the house.
        // We thus need to add l to get to the position of the house.
        // => ax - c - l <= y
        lp.set_a(a, nobel_freshwater_index_over, x);
        lp.set_a(c, nobel_freshwater_index_over, -1);
        lp.set_a(l, nobel_freshwater_index_over, -1);
        lp.set_b(nobel_freshwater_index_over, y);
    }
    
    for (int i = 0; i < m; i++) {
        int x; std::cin >> x;
        int y; std::cin >> y;
        
        // Commonerhouse needs to be on the right of the sewerpipe.
        // => Sewerpipe needs to be on the left of the house.
        // => x + ay + b >= 0
        // <=> -ay - b <= x
        lp.set_a(a, n + i, -y);
        lp.set_a(b, n + i, -1);
        lp.set_b(n + i, x);
        
        // Let x_l be the x-position of the sewerpipe on the same height as the house.
        // Let x_h be the x-position of the house itself.
        // We know that the house is on the right of the sewerpipe, thus we want
        // to know the value x_1 - x_2 and sum that up for all commonerhouses.
        // x_2 + ay + b = 0
        // <=> x_2 = -ay - b
        // => One portion of the sum is x_1 - (-ay - 1*b) = x_1 + ay + b
        ys += y;
        bs += 1;
        xs += x;
        
        int const commoner_freshwater_index_under = 3 * n + m + 2 * i;
        int const commoner_freshwater_index_over = commoner_freshwater_index_under + 1;
        
        lp.set_a(a, commoner_freshwater_index_under, -x);
        lp.set_a(c, commoner_freshwater_index_under, 1);
        lp.set_a(l, commoner_freshwater_index_under, -1);
        lp.set_b(commoner_freshwater_index_under, -y);
        
        lp.set_a(a, commoner_freshwater_index_over, x);
        lp.set_a(c, commoner_freshwater_index_over, -1);
        lp.set_a(l, commoner_freshwater_index_over, -1);
        lp.set_b(commoner_freshwater_index_over, y);
    }
    
    lp.set_l(l, true, 0);
    lp.set_c(l, 1);
    Solution sol = CGAL::solve_linear_program(lp, ET());
    
    if (sol.is_infeasible()) {
        std::cout << "Yuck!" << std::endl;
        return;
    }
    
    if (s != -1) {
        int tywin_constraint_index = 3 * (n + m);
        
        // As we add all these sums together, after simplification we get a sum
        // of the form a * ys + b * bs + xs. We now need this sum to be less or
        // equal to s. Thus we add a new constraint a * ys + b * bs <= s - xs.
        lp.set_a(a, tywin_constraint_index, ys);
        lp.set_a(b, tywin_constraint_index, bs);
        lp.set_b(tywin_constraint_index, s - xs);
        sol = CGAL::solve_linear_program(lp, ET());
        
        if (sol.is_infeasible()) {
            std::cout << "Bankrupt!" << std::endl;
            return;
        }
    }
    
    std::cout << std::setprecision(0) << std::fixed << ceil_to_double(sol.objective_value()) << std::endl;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    int t; std::cin >> t;
    
    for (int i = 0; i < t; i++) {
        testcase();
    }
}
