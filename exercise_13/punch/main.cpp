#include <iostream>
#include <vector>
#include <tuple>
#include <limits>

typedef std::vector<std::vector<std::tuple<int, int, bool>>> dp_type; // cost, -different products, used

std::tuple<int, int, bool> solve(dp_type & dp, std::vector<std::pair<int, int>> const & beverages, int availableBeverages, int requiredLiters) {
    if (requiredLiters <= 0) {
        return {0, 0, false};
    }
    
    if (availableBeverages <= 0) {
        return {std::numeric_limits<int>::max(), 0, false};
    }
    
    if (std::get<0>(dp[availableBeverages][requiredLiters]) != -1) {
        return dp[availableBeverages][requiredLiters];
    }
    
    auto skip = solve(dp, beverages, availableBeverages-1, requiredLiters);
    auto take = solve(dp, beverages, availableBeverages, requiredLiters - beverages[availableBeverages-1].second);
    auto skip_result = std::make_tuple(std::get<0>(skip), std::get<1>(skip), false);
    // By buying the current beverage we will guarantee that we have at least as many liters as required.
    auto take_result = std::make_tuple(std::get<0>(take) + beverages[availableBeverages-1].first, std::get<1>(take) - !std::get<2>(take), true);
    dp[availableBeverages][requiredLiters] = std::min(skip_result, take_result);
    return dp[availableBeverages][requiredLiters];
}

void testcase() {
    int n; std::cin >> n;
    int k; std::cin >> k;
    std::vector<std::pair<int, int>> beverages(n);
    
    for (int i = 0; i < n; i++) {
        int c; std::cin >> c;
        int v; std::cin >> v;
        beverages[i] = {c, v};
    }
    
    dp_type dp(n+1, std::vector<std::tuple<int, int, bool>>(k+1, {-1, 0, false}));
    std::tuple<int, int, bool> best = solve(dp, beverages, n, k);
    std::cout << std::get<0>(best) << " " << -std::get<1>(best) << std::endl;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    int t; std::cin >> t;
    
    for (int i = 0; i < t; i++) {
        testcase();
    }
}
