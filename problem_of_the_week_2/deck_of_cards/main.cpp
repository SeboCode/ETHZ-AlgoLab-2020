#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <iterator>

void testcase() {
    int n; std::cin >> n;
    int k; std::cin >> k;
    std::vector<int> card_values{};
    std::copy_n(std::istream_iterator<int>(std::cin), n, std::back_inserter(card_values));
    std::vector<int> sums{};
    
    sums.push_back(card_values[0]);
    
    for (int i = 1; i < n; i++) {
        sums.push_back(sums[i-1] + card_values[i]);
    }
    
    int start_index = 0;
    int end_index = 0;
    int best_sum = -1;
    
    int j = 0;
    int i = 0;
    
    while (i < n && best_sum != k) {
        int current_sum = 0;
        
        if (j == 0) {
            current_sum = sums[i];
        } else {
            current_sum = sums[i] - sums[j-1];
        }
        
        if (best_sum == -1 || std::abs(k - current_sum) < std::abs(k - best_sum)) {
            start_index = j;
            end_index = i;
            best_sum = current_sum;
        }
        
        if (i == j || current_sum < k) {
            i++;
        } else if (current_sum > k) {
            j++;
        }
    }
    
    std::cout << start_index << " " << end_index << std::endl;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    
    int t; std::cin >> t;
    
    for (int i = 0; i < t; i++) {
        testcase();
    }
}
