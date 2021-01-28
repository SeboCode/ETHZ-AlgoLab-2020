#include <iostream>
#include <string>
#include <iomanip>

void testcase() {
    int i;
    long l;
    std::string s;
    double d;
    std::cin >> i >> l >> s >> d;
    std::cout << std::setprecision(2) << std::fixed << i << " " << l << " " << s << " " << d << std::endl;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    
    int t;
    std::cin >> t;
    
    for (int i = 0; i < t; i++) {
        testcase();
    }
}
