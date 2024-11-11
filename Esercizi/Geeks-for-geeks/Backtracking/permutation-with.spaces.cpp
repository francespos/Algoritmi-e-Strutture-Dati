//{ Driver Code Starts
#include <bits/stdc++.h>
using namespace std;


// } Driver Code Ends

// Complessita': O(2^n)

#include <deque>

using VecBool = std::deque<bool>;
using VecVecBool = std::vector<VecBool>;

VecBool getCandidates() {
    return VecBool{false, true};
}

bool isASolution(const VecBool& position, int n) {
    return position.size() == n;
}

void backtrack(VecBool& position, VecVecBool& solutions, int n) {
    if (isASolution(position, n)) {
        solutions.push_back(position);
        
        /*
        for (auto elem : position) {
            std::cout << elem << " ";
        }
        
        std::cout << "\n";
        */
        
        return;
    }
    
    auto candidates = getCandidates();
    
    for (const auto& candidate : candidates) {
        position.push_back(candidate);
        backtrack(position, solutions, n);
        position.pop_back();        
    }
}

std::string convertToString(const VecBool& position, 
    const std::string& s) 
{
    std::string ret{};
    
    for (int i = 0; i < s.size() - 1; ++i) {
        ret.push_back(s[i]);
        
        if (!position[i]) {
            ret.push_back(' ');
        }
    }
    
    ret.push_back(s.back());
    return ret;
}

using VecStr = std::vector<std::string>;

VecStr convertToVecString(const VecVecBool& solutions, 
    const std::string& s)
{
    VecStr ret{};
    
    for (const auto& solution : solutions) {
        ret.push_back(convertToString(solution, s));
    }
    
    return ret;
}

class Solution {
public:
    vector<string> permutation(string s) {
        VecBool position{};
        VecVecBool solutions{};
        
        backtrack(position, solutions, s.size() - 1);
        
        return convertToVecString(solutions, s);    
    }
};

//{ Driver Code Starts.

int main() {
    int t;
    cin >> t;
    while (t--) {
        string S;
        cin >> S;
        vector<string> ans;
        Solution obj;
        ans = obj.permutation(S);
        for (int i = 0; i < ans.size(); i++) {
            cout << "(" << ans[i] << ")";
        }
        cout << endl;
    
cout << "~" << "\n";
}
}

// } Driver Code Ends