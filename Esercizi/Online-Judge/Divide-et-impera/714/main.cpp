// Mi trovo (almeno con i casi di test forniti), manca solo il calcolo della 
// complessità
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
    const auto q = indicesSeq[1];
    auto r = indicesSeq[2];
    
    const auto leftSum = getSum(v, p, q);
    const auto rightSum = getSum(v, q + 1, r);
    
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
        
        const auto sum = getSum(v, p, r);
        
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

void setPartitionIndicesSeq(const std::vector<int>& v, 
    std::vector<int>& indicesSeq, int pos) 
{
    if (pos == 2) {
        const auto r = indicesSeq[1];
        
        indicesSeq[1] = getPartitionIndex(v, 0, r);
        indicesSeq[2] = r;

        
        setPartitionIndicesSeq(v, indicesSeq, 3);
    } else if (pos != indicesSeq.size()) {
        const auto indices = findMaxSumPartitionIndices(v, indicesSeq, pos);
        
        indicesSeq[pos] = getPartitionIndex(v, indices.p, indices.r);
        std::sort(indicesSeq.begin() + 1, indicesSeq.begin() + pos + 1);
        
        setPartitionIndicesSeq(v, indicesSeq, ++pos);
    }
}

std::vector<int> getPartitionIndices(const std::vector<int>& v, int k) {
    std::vector<int> indicesSeq(k + 1, 0);
    
    indicesSeq[1] = v.size() - 1;
    setPartitionIndicesSeq(v, indicesSeq, 2);
    
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