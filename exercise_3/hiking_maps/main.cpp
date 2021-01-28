#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <vector>

/*
 * We know by the description of the exercise that all hicking locations have
 * coordinates which are < 2^31. As such they need at most 30 bits for representation.
 * Therefore, we can not only us an int to read them from the standard input, but we
 * can also use the inexact kernel. This is due to the fact that CGAL::right_turn()
 * will internally call a subtraction after which it calls a multiplication.
 * The resulting number uses at most (30 + 1) * 2 = 62 bits, which can easily be
 * represented by a double, which the inexact kernel internally uses.
 */
typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef K::Point_2 Point;

bool isLeftOf(Point const &first, Point const &second, std::vector<std::pair<Point, Point>> const &triangle) {
    for (int i = 0; i < 3; i++) {
        if (CGAL::right_turn(triangle[i].first, triangle[i].second, first) ||
            CGAL::right_turn(triangle[i].first, triangle[i].second, second)) {
            return false;
        }
    }
    
    return true;
}

void testcase() {
    int m; std::cin >> m;
    int n; std::cin >> n;
    std::vector<Point> hickingLocations(m);
    
    for (int i = 0; i < m; ++i) {
        int x; std::cin >> x;
        int y; std::cin >> y;
        hickingLocations[i] = Point(x, y);
    }
    
    std::vector<std::vector<std::pair<Point, Point>>> mapParts(n, std::vector<std::pair<Point, Point>>(3));
    
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < 3; j++) {
            int x0; std::cin >> x0;
            int y0; std::cin >> y0;
            int x1; std::cin >> x1;
            int y1; std::cin >> y1;
            mapParts[i][j] = std::make_pair(Point(x0, y0), Point(x1, y1));
        }
        
        for (int j = 0; j < 3; j++) {
            auto first = mapParts[i][j].first;
            auto second = mapParts[i][j].second;
            auto comparison = mapParts[i][(j+1) % 3].first;
            
            if (!CGAL::left_turn(first, second, comparison)) {
                mapParts[i][j] = std::make_pair(second, first);
            }
        }
    }
    
    int min = n;
    int left = 0;
    int right = 0;
    std::vector<int> occurrences(m-1, 0);
    std::vector<std::vector<int>> leftOfMatrix(m-1, std::vector<int>(n, -1));
    int differentLegs = 0;
    
    while (right <= n) {
        // will allways be called if left == right, as in that case all occurrences will be 0.
        if (differentLegs < m-1) {
            if (right == n) {
                break;
            }
            
            for (int i = 0; i < m-1; i++) {
                if (leftOfMatrix[i][right] == -1) {
                    leftOfMatrix[i][right] = isLeftOf(hickingLocations[i], hickingLocations[i+1], mapParts[right]) ? 1 : 0;
                }
                
                if (leftOfMatrix[i][right] == 1) {
                    if (occurrences[i] == 0) {
                        differentLegs++;
                    }
                    
                    occurrences[i]++;
                }
            }
            
            right++;
        } else {
            min = std::min(min, right - left);
            
            for (int i = 0; i < m-1; i++) {
                if (leftOfMatrix[i][left] == -1) {
                    leftOfMatrix[i][left] = isLeftOf(hickingLocations[i], hickingLocations[i+1], mapParts[left]) ? 1 : 0;
                }
                
                if (leftOfMatrix[i][left] == 1) {
                    occurrences[i]--;
                    
                    if (occurrences[i] == 0) {
                        differentLegs--;
                    }
                }
            }
            
            left++;
        }
    }
    
    std::cout << min << std::endl;
}

int main(){
    std::ios_base::sync_with_stdio(false);
    int c; std::cin >> c;
    
    for (int i = 0; i < c; i++) {
        testcase();
    }
}
