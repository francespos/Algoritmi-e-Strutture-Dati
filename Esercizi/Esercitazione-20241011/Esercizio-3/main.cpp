/*
Input:
5
4 2
3 4
10 1
2 2
8 128 
-1
Output:
12
7
512
3
255
La complessita' e' Theta(d), dove d e' la profondita'
dell'albero.
*/
#include <iostream>
#include <cmath>
#include <vector>

int getPos(int pos, int depth, int numBalls) {
    if (depth == 1) {
        return pos;
    }
    
    if (numBalls % 2 == 1) {
        return getPos(2 * pos, depth - 1, (numBalls + 1) / 2); 
    }
    
    return getPos(2 * pos + 1, depth - 1, numBalls / 2);
}

int main() {
    int numTestCases;
    std::cin >> numTestCases;
    
    std::vector<int> results(numTestCases);
    
    for (auto& result : results) {
        int depth, numBalls;
        
        std::cin >> depth;
        std::cin >> numBalls;
    
        result = getPos(1, depth, numBalls);
    }
    
    int endOfInput;
    std::cin >> endOfInput;
    
    for (auto result : results) {
        std::cout << result << "\n";
    }
}