/*
Input:
5
20
1
2
3
6
8
12
13
13
15
16
17
18
19
20
20
21
25
26
30
31
Output:
6 16 20
Complessita':
O(n).
*/
#include <utility>
#include <vector>
#include <iostream>

std::pair<int, int> getIndices(const std::vector<int>& v, int duration) {
    int i = 0, j = 0, maxLeftIndex = 0, maxRightIndex = 0;
   
    while (j < v.size()) {
        if (v[j] - v[i] <= duration - 1) {
            ++j;
        } else {
            if (j - i - 1 > maxRightIndex - maxLeftIndex) {
                maxLeftIndex = i;
                maxRightIndex = j - 1; 
            }
            
            ++i; ++j;
        }
    }
    
    return std::pair<int, int>(maxLeftIndex, maxRightIndex);
}

int main() {
    int duration;
    
    while (std::cin >> duration) {  
        int numYears;
        std::cin >> numYears;
        
        std::vector<int> years(numYears);
        
        for (auto& year : years) {
            std::cin >> year;
        }

        auto indices = getIndices(years, duration);

        std::cout << indices.second - indices.first + 1 << " "
            << years[indices.first] << " " 
            << years[indices.second] << "\n";
    }
}