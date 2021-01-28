#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>

long solve_one_dimensional(std::vector<int>& sums) {
    int sum = 0;
    int even = 0;
    int odd = 0;
    
    for (int k : sums) {
        sum += k;
        
        if (sum % 2 == 0) {
            even++;
        } else {
            odd++;
        }
    }
    
    return even * (even - 1) / 2 + odd * (odd - 1) / 2 + even;
}

void testcase() {
    int n; std::cin >> n;
    std::vector<std::vector<int>> matrix(n, std::vector<int>{});
    
    for (auto& v : matrix) {
        std::copy_n(std::istream_iterator<int>(std::cin), n, std::back_inserter(v));
    }
    
    std::vector<std::vector<int>> sum_matrix(n, std::vector<int>{});
    
    for (int i = 0; i < n; i++) {
        sum_matrix[i].push_back(matrix[i][0]);
        
        for (int j = 1; j < n; j++) {
            sum_matrix[i].push_back(sum_matrix[i][j-1] + matrix[i][j]);
        }
    }
    
    long amount = 0;
    
    for (int i = 0; i < n; i++) {
        for (int j = i; j < n; j++) {
            std::vector<int> sums{};
            
            for (int k = 0; k < n; k++) {
                if (i == 0) {
                    sums.push_back(sum_matrix[k][j]);
                } else {
                    sums.push_back(sum_matrix[k][j] - sum_matrix[k][i-1]);
                }
            }
            
            amount += solve_one_dimensional(sums);
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
