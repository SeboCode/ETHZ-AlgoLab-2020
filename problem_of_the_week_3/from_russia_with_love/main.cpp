#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>

typedef std::vector<std::vector<std::vector<int>>> dp_type;

int solve(dp_type &dp, std::vector<int> const &coins, int passenger, int m, int k, int left, int right) {
    int nextPassenger = (passenger + 1) % m;
    
    if (passenger == k) {
        if (dp[1][left][right] != -1) {
            return dp[1][left][right];
        }
    
        if (left == right) {
            return coins[left];
        }
        
        int pickLeft = solve(dp, coins, nextPassenger, m, k, left+1, right) + coins[left];
        int pickRight = solve(dp, coins, nextPassenger, m, k, left, right-1) + coins[right];
        dp[1][left][right] = std::max(pickLeft, pickRight);
        return dp[1][left][right];
    } else {
        if (dp[0][left][right] != -1) {
            return dp[0][left][right];
        }
    
        if (left == right) {
            return 0;
        }
        
        int pickLeft = solve(dp, coins, nextPassenger, m, k, left+1, right);
        int pickRight = solve(dp, coins, nextPassenger, m, k, left, right-1);
        dp[0][left][right] = std::min(pickLeft, pickRight);
        return dp[0][left][right];
    }
}

void testcase() {
    int n; std::cin >> n;
    int m; std::cin >> m;
    int k; std::cin >> k;
    std::vector<int> coins{};
    std::copy_n(std::istream_iterator<int>(std::cin), n, std::back_inserter(coins));
    dp_type dp(2, std::vector<std::vector<int>>(n, std::vector<int>(n, -1)));
    
    std::cout << solve(dp, coins, 0, m, k, 0, n-1) << std::endl;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    int t; std::cin >> t;
    
    for (int i = 0; i < t; i++) {
        testcase();
    }
}
