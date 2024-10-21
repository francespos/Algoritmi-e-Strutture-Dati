// Non ancora concluso
#include <vector>
#include <algorithm>
#include <iostream>

// Dato un vettore, restituisce la somma degli elementi con indice compreso tra
// p ed r.
int sum(const std::vector<int>& v, int p, int r) {
    int sum = 0;
    
    for (int i = p; i <= r; ++i) {
        sum += v[i];
    }
    
    return sum;
}

// Trova il massimo tra la somma degli elementi compresi tra p e r e la somma
// degli elementi compresi tra r + 1 e s.
int getMax(const std::vector<int>& v, int p, int r, int s) {
    return std::max(sum(v, p, r), sum(v, r + 1, s));
}

struct Indices {
    int p, r;
};

// Dato un vettore e una sequenza di indici crescente che identifica una
// partizione del vettore, restituisce l'indice iniziale della partizione
// la cui somma degli elementi è massima.
int findMaxSumPartitionIndex(const std::vector<int>& v, 
    const std::vector<int>& indices, int pos) 
{
    int max = getMax(v, indices[0], indices[2], indices[1]);
    
    int j = 2;
    
    for (int i = 3; i < pos; ++i) {
        const auto value 
            = getMax(v, indices[i - 2], indices[i], indices[i - 1]);
        if (max < value) {
            max = value;
            j = i;
        }
    }
    
    return indices[j];
}

// 
int getPartitionIndex(const std::vector<int>& v, int p, int r) {
    int leftSum = 0;
    int rightSum = sum(v, p, r);
    
    int q;
    
    for (q = p; leftSum < rightSum; ++q) {
        leftSum += v[q];
        rightSum -= v[q];
    }
    
    return q;
}

void partition(const std::vector<int>& v, std::vector<int>& indices, 
    int pos) 
{
    if (pos == indices.size()) {
        return;
    }
    
    if (pos == 2) {
        indices[2] = getPartitionIndex(v, 0, indices[1]);
        partition(v, indices, 3);
    }

    indices[pos] = getPartitionIndex(v, indices[pos - 1], indices[2]);
    partition(v, indices, ++pos);
}

int main() {
    int k = 3;
    std::vector<int> v{100, 200, 300, 400, 500, 600, 700, 800, 900};
    
    std::vector<int> indices(k, 0);
    indices[1] = v.size() - 1;
    
    partition(v, indices, 2, k);
    
    for (int i = 0; i < k; ++i) {
        std::cout << indices[i] << " ";
    }
    
}