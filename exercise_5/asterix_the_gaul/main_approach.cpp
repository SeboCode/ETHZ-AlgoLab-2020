#include <iostream>
#include <vector>
#include <algorithm>
#include <tuple>

typedef std::vector<std::pair<long, long>> movement_list;
typedef std::vector<std::tuple<long, long, int>> distance_list;
typedef movement_list::size_type movement_list_size_type;
typedef distance_list::size_type distance_list_size_type;

long D;
long T;
distance_list distances1;
distance_list distances2;
std::vector<long> gulpImprovements;

long calculateDistance(std::tuple<long, long, int> const & distance, long gulpImprovement) {
    return std::get<0>(distance) + std::get<2>(distance) * gulpImprovement;
}

long calculateDistance(distance_list const & distances, distance_list_size_type index, long gulpImprovement) {
    return calculateDistance(distances[index], gulpImprovement);
}

bool canReach(long gulpImprovement) {
    for (distance_list distances : std::vector<distance_list>{distances1, distances2}) {
        for (distance_list_size_type i = 0; i < distances.size(); i++) {
            if (calculateDistance(distances, i, gulpImprovement) >= D && std::get<1>(distances[i]) < T) {
                return true;
            }
        }
    }
    
    if (!distances2.empty()) {
        for (auto distanceTuple : distances1) {
            long distance1 = calculateDistance(distanceTuple, gulpImprovement);
            
            // TODO: Binary search instead of iteration
            for (auto distanceTuple2 : distances2) {
                long distance2 = calculateDistance(distanceTuple2, gulpImprovement);
                
                if (distance1 + distance2 >= D && std::get<1>(distanceTuple) + std::get<1>(distanceTuple2) < T) {
                    return true;
                }
            }
        }
    }
    
    return false;
}

int getRequiredGultAmount(int left, int right) {
    if (left == right) {
        return left;
    }
    
    int middle = (right + left) / 2;
    
    if (!canReach(gulpImprovements[middle])) {
        return getRequiredGultAmount(middle+1, right);
    } else {
        return getRequiredGultAmount(left, middle);
    }
}

void computeDistances(distance_list & distances, movement_list const & movements) {
    for (int k = 0; k < 1 << movements.size(); k++) {
        long distance = 0;
        long time = 0;
        int moves = 0;
        
        for (int i = 0; i < movements.size(); i++) {
            if(k & 1 << i) {
                distance += movements[i].first;
                time += movements[i].second;
                moves++;
            }
        }
        
        distances.push_back({ distance, time, moves });
    }
}

void testcase() {
    int n; std::cin >> n;
    int m; std::cin >> m;
    std::cin >> D;
    std::cin >> T;
    movement_list movements1{};
    movement_list movements2{};
    gulpImprovements = std::vector<long>(m+1);
    gulpImprovements[0] = 0;
    
    for (int i = 0; i < n; i++) {
        long d; std::cin >> d;
        long t; std::cin >> t;
        
        if (i <= n/2) {
            movements1.push_back(std::make_pair(d, t));
        } else {
            movements2.push_back(std::make_pair(d, t));
        }
    }
    
    for (int i = 1; i < m+1; i++) {
        std::cin >> gulpImprovements[i];
    }
    
    distances1 = distance_list{};
    distances2 = distance_list{};
    computeDistances(distances1, movements1);
    computeDistances(distances2, movements2);
    std::sort(distances2.begin(), distances2.end());
    
    if (!canReach(gulpImprovements[m])) {
        std::cout << "Panoramix captured" << std::endl;
        return;
    }
    
    std::cout << getRequiredGultAmount(0, m) << std::endl;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    int t; std::cin >> t;
    
    for (int i = 0; i < t; i++) {
        testcase();
    }
}
