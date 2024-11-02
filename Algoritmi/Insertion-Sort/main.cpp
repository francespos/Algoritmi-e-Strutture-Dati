#include <iostream>
#include <vector>
#include <string_view>

template<class RandomIt, class Compare = std::less<>>
constexpr void sort(RandomIt first, RandomIt last, Compare comp = Compare()) {
    for (auto it1 = first + 1; it1 < last; ++it1) {
        auto key = *it1;
        auto it2 = it1;
        
        while (it2 > first && comp(key, *(it2 - 1))) {
            *it2 = *(it2 - 1);
            --it2;
        }
        
        *it2 = key; 
    }
}

int main() {
    struct {
        constexpr bool operator()(int a, int b) const {
            return a < b;    
        }
    } customLess;
    
    struct {
        constexpr bool operator()(int a, int b) const {
            return a > b;    
        }
    } customBigger;
    
    std::vector<int> v{5, 2, 4, 6, 4, 1, 3};
    
    auto printV = [&v](std::string_view message) {
        std::cout << message << ": ";
        
        for (auto elem : v) {
            std::cout << elem << " ";
        }
        
        std::cout << "\n";
    };
    
    sort(v.begin(), v.end());
    printV("Elementi ordinati con comparatore standard");
    
    sort(v.begin(), v.end(), customLess);
    printV("Elementi ordinati con comparatore customLess");
    
    sort(v.begin(), v.end(), customBigger);
    printV("Elementi ordinati con comparatore customBigger");
}