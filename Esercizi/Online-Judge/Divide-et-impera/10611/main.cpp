// Chiamo v la sequenza e x l'elemento fornito.
// int findLeftValue(vector<int>& v, int x, int pos)
// Se v[pos] >= x, ritorna findLeftValue(v, x, pos - 1)
// Se v[pos] < x, ritorna v[pos]
// Se non esiste l'elemento cercato (pos < 0), ritorna -1 (fallimento)
// int findRightValue(vector<int>& v, int x, int pos)
// Se v[pos] <= x, ritorna findRightValue(v, x, pos + 1)
// se v[pos] > x, ritorna v[pos]
// Se non esiste l'elemento cercato (pos >= v.size()), ritorna -1 (fallimento)
// Il caso peggiore e' quello di fallimento, e richiede lo scorrimento di tutta 
// la sequenza. Quindi, la complessita' e' O(n).
#include <vector>
#include <iostream>
#include <string>

int findLeftValue(const std::vector<int>& v, int x, int pos) {
    if (pos < -0) {
        return -1;
    }
    
    if (v[pos] >= x) {
        return findLeftValue(v, x, pos - 1);
    } else {
        return v[pos];
    }
}

int findLeftValue(const std::vector<int>& v, int x) {
    return findLeftValue(v, x, v.size() - 1);
}

int findRightValue(const std::vector<int>& v, int x, int pos) {
    if (pos >= v.size()) {
        return -1;
    }
    
    if (v[pos] <= x) {
        return findRightValue(v, x, pos + 1);
    } else {
        return v[pos];
    }
}

int findRightValue(const std::vector<int>& v, int x) {
    return findRightValue(v, x, 0);
}

int main() {
    int vLenght;
    std::cin >> vLenght;
    std::vector<int> v(vLenght);
    
    for (auto& elem : v) {
        std::cin >> elem;
    }
    
    int xLenght;
    std::cin >> xLenght;
    std::vector<int> xx(xLenght);
    
    for (auto& x : xx) {
        std::cin >> x;
    }

    for (auto x : xx) {
        const auto leftValue = findLeftValue(v, x);
        const auto leftValueString = leftValue > 0 ? std::to_string(leftValue) 
            : "X";
            
        const auto rightValue = findRightValue(v, x);
        const auto rightValueString = rightValue > 0 ? 
            std::to_string(rightValue) : "X";
        
        std::cout << leftValueString << " " << rightValueString << "\n";
    }
}