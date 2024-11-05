/*
Input: 
2
9 3
100 200 300 400 500 600 700 800 900
5 4
100 100 100 100 100
Output:
100 200 300 400 500 / 600 700 / 800 900
100 / 100 / 100 / 100 100
*/
// Per quanto riguarda il calcolo della complessita', osserviamo che ciascuna 
// delle n iterazioni ha complessità nel caso peggiore pari a doppio della
// dimensione della sequenza al momento dell'iterazione (perche' sia 
// l'inserimento in ordine che l'operazione per determinare l'indice della 
// partizione hanno complessita' lineare), per cui:
// T(n) = sum_{i=2}^n i.
// Facendo i calcoli, si ottiene O(n^2).
#include <vector>
#include <iostream>
#include <algorithm>

int getSum(const std::vector<int>& v, int p, int r) {
    int sum = 0;
    
    for (int i = p; i <= r; ++i) {
        sum += v[i];
    }
    
    return sum;
}

struct Indices {
    int p, r;
};

Indices findMaxSumPartitionIndices(const std::vector<int>& v, 
    const std::vector<int>& indicesSeq, int pos) 
{
    Indices indices;
    int max;

    auto p = indicesSeq[0];
    auto q = indicesSeq[1];
    auto r = indicesSeq[2];
    
    auto leftSum = getSum(v, p, q);
    auto rightSum = getSum(v, q + 1, r);
    
    if (leftSum < rightSum) {
        indices.p = q + 1;
        indices.r = r;
        max = rightSum;
    }
    
    indices.p = p;
    indices.r = q;
    
    max = leftSum;
    
    for (int i = 2; i < pos - 2; ++i) {
        p = indicesSeq[i];
        r = indicesSeq[i + 1];
        
        auto sum = getSum(v, p, r);
        
        if (sum > max) {
            indices.p = p;
            indices.r = r;
            max = sum;
        }
    }
    
    return indices;
}

int getPartitionIndex(const std::vector<int>& v, int p, int r) {
    int leftSum = 0;
    int rightSum = getSum(v, p, r);
    
    int q;
    
    for (q = p; leftSum < rightSum; ++q) {
        leftSum += v[q];
        rightSum -= v[q];
    }
    
    return q - 1;
}

void insertInOrder(std::vector<int>& indicesSeq, int index) {
    int i = 0;
    
    while (index > indicesSeq[i]) {
        ++i;
    }
    
    indicesSeq.insert(indicesSeq.begin() + i, index);
}

void setPartitionIndicesSeq(const std::vector<int>& v, 
    std::vector<int>& indicesSeq, int pos, int k) 
{
    if (pos == 2) {
        insertInOrder(indicesSeq, getPartitionIndex(v, 0, indicesSeq[1]));
        
        setPartitionIndicesSeq(v, indicesSeq, 3, k);
    } else if (pos < k) {
        const auto indices = findMaxSumPartitionIndices(v, indicesSeq, pos);
        
        const auto partitionIndex = getPartitionIndex(v, indices.p, indices.r);
        insertInOrder(indicesSeq, partitionIndex);
        
        setPartitionIndicesSeq(v, indicesSeq, pos + 1, k);
    }
}

std::vector<int> getPartitionIndices(const std::vector<int>& v, int k) {
    std::vector<int> indicesSeq{0, static_cast<int>(v.size() - 1)};

    setPartitionIndicesSeq(v, indicesSeq, 2, k + 1);
    
    return indicesSeq;
}

void printPartition(const std::vector<int>& v, 
    const std::vector<int>& indicesSeq)
{
    int j = 1;
    
    for (int i = 0; i < v.size(); ++i) {
        std::cout << v[i] << " ";
        
        if (indicesSeq[j] == i) {
            std::cout << "/ ";
            
            if (j < indicesSeq.size() - 2) {
                ++j;
            }
        }
    }
}

int main() {
    int numTestCases;
    std::cin >> numTestCases;
    
    std::vector<std::vector<int>> vv(numTestCases);
    std::vector<std::vector<int>> indicesSeqs(numTestCases);
    
    for (int i = 0; i < numTestCases; ++i) {
        int m;
        std::cin >> m;
        
        std::vector<int> v(m);
        
        int k;
        std::cin >> k;
        
        for (int j = 0; j < m; ++j) {
            std::cin >> v[j];
        }
        
        vv[i] = v;
        indicesSeqs[i] = getPartitionIndices(v, k);
    }
    
    for (int i = 0; i < numTestCases; ++i) {
        printPartition(vv[i], indicesSeqs[i]);
        std::cout << "\n";
    }
}