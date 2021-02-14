#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>

void testcase() {
    int n; std::cin >> n;
    int k; std::cin >> k;
    std::vector<int> card_values{};
    std::copy_n(std::istream_iterator<int>(std::cin), n, std::back_inserter(card_values));
    int left = 0;
    int right = 1;
    int current_sum = card_values[0];
    int start_index = 0;
    int end_index = 0;
    int best_sum = current_sum;
    
    while (right <= n && best_sum != k) {
        if (std::abs(k - current_sum) < std::abs(k - best_sum)) {
            start_index = left;
            end_index = right-1;
            best_sum = current_sum;
        }
        
        if (current_sum < k) {
            if (right == n) {
                break;
            }
            
            current_sum += card_values[right];
            right++;
        } else {
            current_sum -= card_values[left];
            left++;
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
