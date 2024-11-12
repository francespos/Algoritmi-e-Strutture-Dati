/*
Input:
4
1 4 5 7
4
4 6 8 10
Output:
1 5
5 7
7 X
7 X
Complessita': O(n)
Osserviamo che essendo la sequenza non descrescente non e' possibile applicare
la ricerca binaria.
*/
#include <vector>
#include <iostream>
#include <string>
#include <utility>

std::pair<int, int> getValues(const std::vector<int>& v, int x) {
    int left = -1;
    int right = -1;
    
    bool rightFound = false;
    
    for (int i = 0; i < v.size(); ++i) {
        if (x > v[i]) {
            left = v[i];
        } else if (!rightFound && x < v[i]) {
            right = v[i];
            rightFound = true;
        }
    }
    
    return std::pair<int, int>(left, right);
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
        auto values = getValues(v, x);
        
        auto print = [](int value) {
            std::cout << (value < 0 ? "X" : std::to_string(value));  
        };
        
        print(values.first);
        std::cout << " ";
        
        print(values.second);
        std::cout << "\n";
    }
}