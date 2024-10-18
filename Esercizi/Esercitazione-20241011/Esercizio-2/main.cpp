#include <vector>
#include <iostream>
#include <algorithm>
#include <cmath>

int findMedian(std::vector<int>& v) {
    const auto n = v.size();
    std::sort(v.begin(), v.begin() + n);
    
    if (n % 2 == 1) {
        return v[n/2];
    } else {
        return (v[n/2 - 1] + v[n/2]) / 2;
    }
}

int findMinSumOfDistances(std::vector<int>& v) {
    const auto median = findMedian(v);
    int sum = 0;
    
    for (auto elem : v) {
        sum += std::abs(median - elem);
    }
    
    return sum;
}

int main() {
    int numTestCases;
    
    std::cin >> numTestCases;
    std::vector<int> mins(numTestCases);
    
    for (int i = 0; i < numTestCases; ++i) {
        int n;
        
        std::cin >> n;
        std::vector<int> v(n);
        
        for (int j = 0; j < n; ++j) {
            std::cin >> v[j];
        }
        
        mins[i] = findMinSumOfDistances(v);
    }
    
    for (int i = 0; i < numTestCases; ++i) {
        std::cout << mins[i] << "\n";
    }
}