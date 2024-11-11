//{ Driver Code Starts
//Initial Template for C++

#include <bits/stdc++.h>
using namespace std;


// } Driver Code Ends
//User function Template for C++

// Complessita': O(n!)

#include <vector>
#include <deque>

using VecInt = std::vector<int>;
using VecVecInt = std::vector<std::vector<int>>;
using VecBool = std::deque<bool>;

bool isASolution(const VecInt& positions, const VecInt& numbers) {
    return positions.size() == numbers.size();
}

bool backtrack(VecInt& positions, VecInt& solution,
    const VecInt& numbers, VecBool& used, int& count, int k)
{
    if (isASolution(positions, numbers) && count == k) {
        solution = positions;
        return true;
    }
    
    if (isASolution(positions, numbers)) {
        ++count;
        return false;
    }
    
    for (int i = 0; i < numbers.size(); ++i) {
        if (used[i]) {
            continue;
        }
        
        used[i] = true;
        positions.push_back(numbers[i]);
        
        if (backtrack(positions, solution, 
            numbers, used, count, k))
        {
            return true;
        }
        
        positions.pop_back();
        used[i] = false;
    }
    
    return false;
}

VecInt getKthPermutation(int n, int k) {
    VecInt positions{};
    VecInt numbers(n);
    
    for (int i = 0; i < n; ++i) {
        numbers[i] = i + 1;
    }
    
    VecBool used(n, false);
    VecInt solution{};
    
    int count = 1;
    backtrack(positions, solution, numbers, used, 
        count, k);
    
    return solution;
}

std::string convertToString(const VecInt& v) {
    std::string ret{};
    
    for (auto elem : v) {
        ret.push_back(elem + '0');
    }
    
    return ret;
}

class Solution {
public:
    std::string kthPermutation(int n, int k) {
        return convertToString(getKthPermutation(n, k));
    }
};

//{ Driver Code Starts.

int main()
{
    int t;
    cin >> t;
    while (t--)
    {
        int n, k;
        cin >> n >> k;
        Solution ob;
        string ans = ob.kthPermutation(n, k);
        cout << ans;
        cout << "\n";
    
cout << "~" << "\n";
}
    return 0;
}

// } Driver Code Ends