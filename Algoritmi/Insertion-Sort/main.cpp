#include <concepts>
#include <iostream>
#include <vector>
#include <cstddef>

template<typename T> requires std::totally_ordered<T>
void insertionSort(std::vector<T>& v) {
    for (int i = 1; i < v.size(); ++i) {
        const auto key = v[i];
        auto j = i - 1;

        while (j >= 0 & v[j] > key) {
            v[j + 1] = v[j];
            --j;
        }

        v[j + 1] = key;
    }
}

int main() {
    std::vector<int> v{5, 2, 4, 6, 1, 3};
    insertionSort(v);

    for (const auto& elem : v) {
        std::cout << elem << " ";
    }
}