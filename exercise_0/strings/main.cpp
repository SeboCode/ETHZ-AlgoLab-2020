#include <iostream>
#include <algorithm>
#include <string>

void testcase() {
    std::string a, b;
    std::cin >> a >> b;
    std::cout << a.length() << b.length() << '\n';
    std::cout << a << b << '\n';
    std::reverse(a.begin(), a.end());
    std::reverse(b.begin(), b.end());
    std::swap(a[0], b[0]);
    std::cout << a << ' ' << b << std::endl;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    
    int t;
    std::cin >> t;
    
    for (int i = 0; i < t; i++) {
        testcase();
    }
}
