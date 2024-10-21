// Non ancora concluso, ma quasi
#include <vector>
#include <iostream>

int sum(const std::vector<int>& v, int p, int r) {
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

    {
        const auto p = indicesSeq[0];
        const auto q = indicesSeq[1];
        const auto r = indicesSeq[2];
        
        const auto leftSum = sum(v, p, q);
        const auto rightSum = sum(v, q + 1, r);
        
        if (leftSum < rightSum) {
            indices.p = q + 1;
            indices.r = r;
        }
        
        indices.p = p;
        indices.r = q;
    }
    
    for (int i = 1; i < pos - 2; ++i) {
        const auto p = indicesSeq[i];
        const auto q = indicesSeq[i + 1];
        const auto r = indicesSeq[i + 2];
        
        const auto leftSum = sum(v, p, q);
        const auto rightSum = sum(v, q + 1, r);
        
        if (leftSum < rightSum) {
            indices.p = q + 1;
            indices.r = r;
        }
        
        indices.p = p;
        indices.r = q;   
    }
    
    return indices;
}

int getPartitionIndex(const std::vector<int>& v, int p, int r) {
    int leftSum = 0;
    int rightSum = sum(v, p, r);
    
    int q;
    
    for (q = p; leftSum < rightSum; ++q) {
        leftSum += v[q];
        rightSum -= v[q];
    }
    
    return q - 1;
}

void partition(const std::vector<int>& v, std::vector<int>& indicesSeq, int pos) 
{
    if (pos == 2) {
        const auto r = indicesSeq[1];
        
        indicesSeq[1] = getPartitionIndex(v, 0, r);
        indicesSeq[2] = r;
        
        partition(v, indicesSeq, 3);
    } else if (pos != indicesSeq.size()) {
        const auto r = indicesSeq[pos - 1];
        const auto indices = findMaxSumPartitionIndices(v, indicesSeq, pos);
        
        indicesSeq[pos - 1] = getPartitionIndex(v, indices.p, indices.r);
        indicesSeq[pos] = r;
        
        partition(v, indicesSeq, ++pos);
    }
}

int main() {
    int k = 4 // correggere;
    std::vector<int> v{100, 200, 300, 400, 500, 600, 700, 800, 900};
    
    std::vector<int> indicesSeq(k, 0);
    indicesSeq[1] = v.size() - 1;
    
    partition(v, indicesSeq, 2);
    
    for (int i = 0; i < k; ++i) {
        std::cout << indicesSeq[i] << " ";
    }
}