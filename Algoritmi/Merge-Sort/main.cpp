#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>

namespace Dsa {
    template<class RandomIt, class Compare = std::less<>>
    constexpr void merge(RandomIt first, RandomIt mid, RandomIt last, 
        Compare comp = Compare()) 
    {
        auto leftSize = std::distance(first, mid);
        auto rightSize = std::distance(mid, last);
    
        std::vector<typename std::iterator_traits<RandomIt>::value_type> left(
            first, mid);
        std::vector<typename std::iterator_traits<RandomIt>::value_type> right(
            mid, last);
            
        auto leftIt = left.begin();
        auto rightIt = right.begin();
        auto resultIt = first;
    
        while (leftIt != left.end() && rightIt != right.end()) {
            if (comp(*rightIt, *leftIt)) {
                *resultIt++ = *rightIt++;
            } else {
                *resultIt++ = *leftIt++;
            }
        }
    
        while (leftIt != left.end()) {
            *resultIt++ = *leftIt++;
        }
    
        while (rightIt != right.end()) {
            *resultIt++ = *rightIt++;
        }
    }
    
    template<class RandomIt, class Compare = std::less<>>
    constexpr void sort(RandomIt first, RandomIt last, Compare comp = Compare())
    {
        auto length = std::distance(first, last);
        
        if (length > 1) {
            auto mid = std::next(first, length / 2);
            
            Dsa::sort(first, mid, comp);
            Dsa::sort(mid, last, comp);
            
            Dsa::merge(first, mid, last, comp);
        }
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
    
    Dsa::sort(v.begin(), v.end());
    printV("Elementi ordinati con comparatore standard");
    
    Dsa::sort(v.begin(), v.end(), customLess);
    printV("Elementi ordinati con comparatore customLess");
    
    Dsa::sort(v.begin(), v.end(), customBigger);
    printV("Elementi ordinati con comparatore customBigger");
}