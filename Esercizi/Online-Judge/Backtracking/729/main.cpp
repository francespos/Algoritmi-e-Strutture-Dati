/*
Input:
1
4 2

Output:
0011
0101
0110
1001
1010
1100
Complessita': O(2^n)
*/
#include <vector>
#include <iostream>

using VecInt = std::vector<int>;
using VecVecInt = std::vector<VecInt>;

bool isASolution(const VecInt& positions, int n) {
    return positions.size() == n;
}

VecInt getCandidates() {
    return VecInt{0, 1};
}

void backtrack(VecInt& positions, VecVecInt& solutions, int n) {
    if (isASolution(positions, n)) {
        solutions.push_back(positions);
        return;
    }
    
    auto candidates = getCandidates();
    
    for (const auto& candidate : candidates) {
        positions.push_back(candidate);
        backtrack(positions, solutions, n);
        positions.pop_back();
    }
}

bool hasKOnes(const VecInt& positions, int k) {
    int numOnes = 0;
    
    for (const auto& position : positions) {
        if (position == 1) {
            ++numOnes;
        }
    }
    
    return numOnes == k;
}

VecVecInt findAllSubsets(int n) {
    VecInt positions{};
    VecVecInt solutions{};
    
    backtrack(positions, solutions, n);   
    return solutions;
}

VecVecInt findAllSubsetsWithKOnes(int n, int k) {
    VecVecInt ret{};
    auto solutions = findAllSubsets(n);
    
    for (const auto& solution : solutions) {
        if (hasKOnes(solution, k)) {
            ret.push_back(solution);
        }
    }
    
    return ret;   
}

std::string convertToString(const VecInt& v) {
    std::string ret{};
    
    for (const auto& elem : v) {
        ret.push_back(elem + '0');
    }
    
    return ret;
}

std::string convertToString(const VecVecInt& v) {
    std::string ret{};
    
    for (const auto& elem : v) {
        ret.append(convertToString(elem));
        ret.push_back('\n');
    }
    
    return ret;
}

int main() {
    int numTestCases;
    std::cin >> numTestCases;
    
    std::cin.ignore();
    
    bool firstTestCase = true;

    while (numTestCases--) {
        if (!firstTestCase) {
            std::cout << "\n";
        }
        
        firstTestCase = false;
        
        int n, h;
        std::cin >> n >> h;
        
        std::cin.ignore();
        
        VecVecInt subsets = findAllSubsetsWithKOnes(n, h);
        std::vector<std::string> resultStrings;
        
        for (const auto& subset : subsets) {
            resultStrings.push_back(convertToString(subset));
        }
        
        for (const auto& str : resultStrings) {
            std::cout << str << "\n";
        }
    }
}