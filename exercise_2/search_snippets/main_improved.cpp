#include <iostream>
#include <vector>
#include <algorithm>

void testcase() {
    int n; std::cin >> n;
    std::vector<int> wordCount(n);
    
    for (int i = 0; i < n; i++) {
        int m; std::cin >> m;
        wordCount[i] = m;
    }
    
    std::vector<std::pair<int, int>> wordPositions{};
    
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < wordCount[i]; j++) {
            int p; std::cin >> p;
            wordPositions.push_back({p, i});
        }
    }
    
    std::sort(wordPositions.begin(), wordPositions.end());
    int left = 0;
    int right = 0;
    int unfoundWordCounter = n;
    int shortestIntervalSize = wordPositions[wordPositions.size()-1].first;
    std::vector<int> occurences(n, 0);
    
    while (right <= wordPositions.size()) {
        if (unfoundWordCounter > 0) {
            if (right == wordPositions.size()) {
                break;
            }
            
            int word = wordPositions[right].second;
            
            if (occurences[word] == 0) {
                unfoundWordCounter--;
            }
            
            occurences[word]++;
            right++;
        } else {
            shortestIntervalSize = std::min(shortestIntervalSize, wordPositions[right-1].first - wordPositions[left].first + 1);
            int word = wordPositions[left].second;
            occurences[word]--;
            
            if (occurences[word] == 0) {
                unfoundWordCounter++;
            }
            
            left++;
        }
    }
    
    std::cout << shortestIntervalSize << std::endl;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    int t; std::cin >> t;
    
    for (int i = 0; i < t; i++) {
        testcase();
    }
}
