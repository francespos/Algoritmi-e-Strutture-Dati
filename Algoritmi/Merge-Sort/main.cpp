#include <concepts>
#include <iostream>
#include <vector>

template<typename T> requires std::totally_ordered<T>
void merge(std::vector<T>& v, int p, int q, int r) noexcept {
    const auto leftSize = q - p + 1;
    const auto rightSize = r - q;

    std::vector<T> left(v.begin() + p, v.begin() + q + 1);
    std::vector<T> right(v.begin() + q + 1, v.begin() + r + 1);
    
    int i = 0, j = 0;
    int k = p; 

    while (i < leftSize && j < rightSize) {
        if (left[i] <= right[j]) {
            v[k++] = left[i++];
        } else {
            v[k++] = right[j++];
        }
    }

    while (i < leftSize) {
        v[k++] = left[i++];
    }

    while (j < rightSize) {
        v[k++] = right[j++];
    }
}

template<typename T> requires std::totally_ordered<T>
void sort(std::vector<T>& v, int p, int r) noexcept {
    if (p < r) {
        const int q = (p + r) / 2;
        
        sort(v, p, q);
        sort(v, q + 1, r);
        
        merge(v, p, q, r);
    }
}

template<typename T> requires std::totally_ordered<T>
void sort(std::vector<T>& v) noexcept {
    sort(v, 0, v.size() - 1);
}

int main() {
    std::vector<int> v{8, 5, 7, 3, 4, 9};
    sort(v);
    
    for(auto elem : v) {
        std::cout << elem << " ";
    }
}