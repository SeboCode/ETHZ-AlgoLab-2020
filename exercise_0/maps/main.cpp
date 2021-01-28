#include <iostream>
#include <map>
#include <vector>
#include <utility>
#include <algorithm>
#include <iterator>
#include <string>

void testcase() {
    int q; std::cin >> q;
    std::multimap<std::string, int> m{};
    
    for (int i = 0; i < q; i++) {
        int a; std::cin >> a;
        std::string b; std::cin >> b;
        
        if (a == 0) {
            m.erase(b);
        } else {
            m.insert({b, a});
        }
    }
    
    std::string d; std::cin >> d;
    
    if (m.empty()) {
        std::cout << "Empty" << std::endl;
    } else {
        auto range = m.equal_range(d);
        std::vector<int> v{};
        
        for (auto it = range.first; it != range.second; it++) {
            v.push_back(it->second);
        }
        
        std::sort(v.begin(), v.end());
        std::copy(v.cbegin(), v.cend(), std::ostream_iterator<int>(std::cout, " "));
        std::cout << std::endl;
    }
}

int main() {
    std::ios_base::sync_with_stdio(false);
    
    int t; std::cin >> t;
    
    for (int i = 0; i < t; i++) {
        testcase();
    }
}
