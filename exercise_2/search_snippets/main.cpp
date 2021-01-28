#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>
#include <utility>

void testcase() {
    int n; std::cin >> n;
    std::vector<int> readVector{};
    std::copy_n(std::istream_iterator<int>(std::cin), n, std::back_inserter(readVector));
    std::vector<std::pair<int, int>> positions{};
    
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < readVector[i]; j++) {
            int p; std::cin >> p;
            positions.push_back(std::make_pair(p, i));
        }
    }
    
    std::sort(positions.begin(), positions.end());
    
    int fillAmount = 0;
    std::vector<int> occurences(n, 0);
    std::vector<std::pair<int, int>>::size_type left = 0;
    std::vector<std::pair<int, int>>::size_type right = 0;
    
    while (fillAmount < n) {
        if (occurences[positions[right].second] == 0) {
            fillAmount++;
        }
        
        occurences[positions[right].second]++;
        right++;
    }
    
    int shortestDistance = positions[right-1].first - positions[left].first + 1;
    int missingIndex = positions[left].second;
    
    while (right < positions.size()) {
        if (occurences[missingIndex] != 0) {
            shortestDistance = std::min(shortestDistance, positions[right-1].first - positions[left].first + 1);
            occurences[positions[left].second]--;
            
            if (occurences[positions[left].second] == 0) {
                missingIndex = positions[left].second;
            }
            
            left++;
        } else {
            occurences[positions[right].second]++;
            right++;
        }
    }
    
    std::cout << shortestDistance << std::endl;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    int t; std::cin >> t;
    
    for (int i = 0; i < t; i++) {
        testcase();
    }
}
