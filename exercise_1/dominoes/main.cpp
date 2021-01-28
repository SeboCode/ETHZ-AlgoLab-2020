#include <iostream>
#include <vector>

void testcase() {
    int n; std::cin >> n;
    std::vector<int> heights{};
    
    for (int i = 0; i < n; i++) {
        int k; std::cin >> k;
        heights.push_back(k);
    }
    
    int toppleHeight = heights[0];
    int amount = 1;
    
    for (int i = 1; i < n; i++) {
        toppleHeight--;
        
        if (toppleHeight == 0) {
            break;
        }
        
        if (toppleHeight < heights[i]) {
            toppleHeight = heights[i];
        }
        
        amount++;
    }
    
    std::cout << amount << std::endl;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    
    int t; std::cin >> t;
    
    for (int i = 0; i < t; i++) {
        testcase();
    }
}
