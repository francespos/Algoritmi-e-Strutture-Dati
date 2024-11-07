/*
Input:
2 
4 
1 3 5 9 
6 
3 6 12 15 18 21 
Output:
7 
9 
Complessita':
O(log n)
*/
#include <iostream>
#include <vector>

int findSequenceConstant(const std::vector<int>& v) {
    auto diff1 = v[1] - v[0];
    auto diff2 = v[2] - v[1];
    
    if (diff1 <= diff2) {
        return diff1;
    }
    
    return diff2;
} 

int findMissingItem(const std::vector<int>& v, int p, int r, int k) {
    if (r - p == 0) {
        return -1;
    }
    
    if (r - p == 1) {
        if (v[p + 1] - v[p] == k) {
            return -1;
        }
        
        return v[p] + k;
    }
    
    int q = (p + r) / 2;
    
    auto missingLeft = findMissingItem(v, p, q, k);
    auto missingRight = findMissingItem(v, q + 1, r, k);
    
    if (missingLeft == -1 && missingRight == -1) {
        return v[q] + k;
    } 
    
    return missingLeft != -1 ? missingLeft : missingRight; 
}

int main() {
    int numTestCases;
    
    std::cin >> numTestCases;
    std::vector<int> missingItems(numTestCases);
    
    for (int i = 0; i < numTestCases; ++i) {
        int vSize;
        
        std::cin >> vSize;
        std::vector<int> v(vSize);
        
        for (int j = 0; j < vSize; ++j) {
            std::cin >> v[j];
        }
        
        auto k = findSequenceConstant(v); 
        missingItems[i] = findMissingItem(v, 0, v.size() - 1, k);
    }

    for (int i = 0; i < numTestCases; ++i) {
        std::cout << missingItems[i] << "\n";
    }
}