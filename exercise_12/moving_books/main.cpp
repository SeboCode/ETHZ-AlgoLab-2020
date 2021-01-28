#include <iostream>
#include <vector>
#include <set>
#include <algorithm>

void testcase() {
    int n; std::cin >> n;
    int m; std::cin >> m;
    std::vector<int> strengths(n);
    std::multiset<int, std::greater<int>> weights{};
    int maxStrength = -1;
    int maxWeight = -1;
    
    for (int i = 0; i < n; i++) {
        int s; std::cin >> s;
        strengths[i] = s;
        maxStrength = std::max(maxStrength, s);
    }
    
    for (int i = 0; i < m; i++) {
        int w; std::cin >> w;
        weights.insert(w);
        maxWeight = std::max(maxWeight, w);
    }
    
    std::sort(strengths.begin(), strengths.end(), std::greater<int>());
    
    if (maxStrength < maxWeight) {
        std::cout << "impossible" << std::endl;
        return;
    }
    
    int rounds = 0;
    
    while (!weights.empty()) {
        rounds++;
        
        for (int i = 0; i < n; i++) {
            auto it = weights.lower_bound(strengths[i]);
            
            if (it != weights.end()) {
                weights.erase(it);
            } else {
                break;
            }
        }
    }
    
    std::cout << 3 * rounds - 1 << std::endl;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    int t; std::cin >> t;
    
    for (int i = 0; i < t; i++) {
        testcase();
    }
}
