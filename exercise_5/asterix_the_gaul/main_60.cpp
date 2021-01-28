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
distance_list distances;
std::vector<long> gulpImprovements;

long calculateDistance(distance_list const & distances, distance_list_size_type index, long gulpImprovement) {
    return std::get<0>(distances[index]) + std::get<2>(distances[index]) * gulpImprovement;
}

bool canReach(long gulpImprovement) {
    for (distance_list_size_type i = 0; i < distances.size(); i++) {
        if (calculateDistance(distances, i, gulpImprovement) >= D && std::get<1>(distances[i]) < T) {
            return true;
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
    movement_list movements{};
    gulpImprovements = std::vector<long>(m+1);
    gulpImprovements[0] = 0;
    
    for (int i = 0; i < n; i++) {
        long d; std::cin >> d;
        long t; std::cin >> t;
        movements.push_back(std::make_pair(d, t));
    }
    
    for (int i = 1; i < m+1; i++) {
        std::cin >> gulpImprovements[i];
    }
    
    distances = distance_list{};
    computeDistances(distances, movements);
    
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
