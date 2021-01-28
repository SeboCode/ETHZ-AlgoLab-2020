#include <iostream>
#include <vector>
#include <string>
#include <iterator>
#include <algorithm>
#include <boost/graph/max_cardinality_matching.hpp>
#include <boost/graph/adjacency_list.hpp>

typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::undirectedS> undirected_graph;
typedef boost::graph_traits<undirected_graph>::vertex_descriptor vertex_descriptor;

int countOverlapingCourses(std::vector<std::string> const & firstStudent, std::vector<std::string> const & secondStudent, int c) {
    int counter = 0;
    int firstStudentPosition = 0;
    int secondStudentPosition = 0;
    
    while (firstStudentPosition < c && secondStudentPosition < c) {
        if (firstStudent[firstStudentPosition] == secondStudent[secondStudentPosition]) {
            counter++;
            firstStudentPosition++;
            secondStudentPosition++;
        } else if (firstStudent[firstStudentPosition] < secondStudent[secondStudentPosition]) {
            firstStudentPosition++;
        } else {
            secondStudentPosition++;
        }
    }
    
    return counter;
}

void testcase() {
    int n; std::cin >> n;
    int c; std::cin >> c;
    int f; std::cin >> f;
    std::vector<std::vector<std::string>> studentCourses(n, std::vector<std::string>{});
    
    for (int i = 0; i < n; i++) {
        std::copy_n(std::istream_iterator<std::string>(std::cin), c, std::back_inserter(studentCourses[i]));
        std::sort(studentCourses[i].begin(), studentCourses[i].end());
    }
    
    undirected_graph graph(n);
    
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < i; j++) {
            if (countOverlapingCourses(studentCourses[i], studentCourses[j], c) > f) {
                boost::add_edge(i, j, graph);
            }
        }
    }
    
    std::vector<vertex_descriptor> mateMap(n);
    boost::edmonds_maximum_cardinality_matching(graph,
        boost::make_iterator_property_map(mateMap.begin(),
            boost::get(boost::vertex_index, graph)));
    int buddyCount = boost::matching_size(graph,
        boost::make_iterator_property_map(mateMap.begin(),
            boost::get(boost::vertex_index, graph)));
    
    if (buddyCount * 2 == n) {
        std::cout << "not optimal" << std::endl;
    } else {
        std::cout << "optimal" << std::endl;
    }
}

int main() {
    std::ios_base::sync_with_stdio(false);
    int t; std::cin >> t;
    
    for (int i = 0; i < t; i++) {
        testcase();
    }
}
