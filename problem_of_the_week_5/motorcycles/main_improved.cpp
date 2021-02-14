#include <iostream>
#include <vector>
#include <stack>
#include <tuple>
#include <CGAL/Gmpq.h>

void testcase() {
    int n; std::cin >> n;
    std::vector<std::tuple<long, CGAL::Gmpq, int>> bikers(n);
    
    for (int i = 0; i < n; i++) {
        long y0; std::cin >> y0;
        long x1; std::cin >> x1;
        long y1; std::cin >> y1;
        bikers[i] = std::make_tuple(y0, CGAL::Gmpq(y1 - y0, x1), i);
    }
    
    std::sort(bikers.begin(), bikers.end());
    std::stack<std::pair<CGAL::Gmpq, int>> stack{};
    
    for (auto biker : bikers) {
        while (true) {
            // The second check tests if the two bikers intersect. They don't
            // intersect, if and only if the biker with smaller starting point
            // has a smaller slop than the one we look at (check all 4 cases).
            if (stack.empty() || stack.top().first <= std::get<1>(biker)) {
                stack.push({std::get<1>(biker), std::get<2>(biker)});
                break;
            } else if (CGAL::abs(stack.top().first) > CGAL::abs(std::get<1>(biker))) {
                stack.pop();
            } else {
                break;
            }
        }
    }
    
    std::vector<int> solution{};
    
    while (!stack.empty()) {
        solution.push_back(stack.top().second);
        stack.pop();
    }
    
    std::sort(solution.begin(), solution.end());
    
    for (int i = 0; i < solution.size(); i++) {
        std::cout << solution[i] << ' ';
    }
    
    std::cout << std::endl;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    int t; std::cin >> t;
    
    for (int i = 0; i < t; i++) {
        testcase();
    }
}
