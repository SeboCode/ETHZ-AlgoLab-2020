#include <iostream>
#include <vector>
#include <algorithm>

void testcase() {
    int n; std::cin >> n;
    std::vector<std::pair<int, int>> boats(n);
    
    for (int i = 0; i < n; i++) {
        int l; std::cin >> l;
        int p; std::cin >> p;
        boats[i] = { p, l };
    }
    
    std::sort(boats.begin(), boats.end());
    int amount = 1;
    int previousPreviousRight = boats[0].first;
    int previousRight = previousPreviousRight;
    
    for (int i = 1; i < n; i++) {
        int currentPosition = boats[i].first;
        int currentLength = boats[i].second;
        
        if (previousRight <= currentPosition) {
            amount++;
            previousPreviousRight = previousRight;
            previousRight = std::max(previousRight + currentLength, currentPosition);
        } else {
            previousRight = std::min(previousRight, previousPreviousRight + currentLength);
            previousRight = std::max(previousRight, currentPosition);
        }
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
