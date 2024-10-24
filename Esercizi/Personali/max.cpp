// Trovare il massimo di una sequenza di numeri positivi in maniera ricorsiva.
#include <iostream>
#include <vector>

int max(const std::vector<int>& v, int oldMax, int pos) {
    if (pos < v.size()) {
        int value = v[pos];
        
        if (value > oldMax) {
            return max(v, value, pos + 1);
        }
        
        return max(v, oldMax, pos + 1);
    }
    
    return oldMax;
}

int max(const std::vector<int>& v) {
    return max(v, v[0], 1);
}

int main() {
    std::vector<int> v{5, 8, 3, 15, 9, 7};
    std::cout << "Max = " << max(v) << "\n";
}