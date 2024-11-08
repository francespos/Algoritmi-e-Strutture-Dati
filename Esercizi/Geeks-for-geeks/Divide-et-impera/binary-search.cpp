//{ Driver Code Starts
// Initial template for C++

#include <bits/stdc++.h>
using namespace std;


// } Driver Code Ends
// User function template for C++

class Solution {
  public:
    int binarySearch(std::vector<int>& v, int k, int p, int r) {
        if (r - p < 0) {
            return -1;
        }
        
        int q = (p + r) / 2;
        
        if (k == v[q]) {
            return q;
        }
        
        if (k < v[q]) {
            return binarySearch(v, k, p, q - 1);
        }
        
        return binarySearch(v, k, q + 1, r); 
    }
  
    int binarysearch(vector<int> &arr, int k) {
        return binarySearch(arr, k, 0, arr.size() - 1);
    }
};

//{ Driver Code Starts.
int main() {
    int t;
    cin >> t;
    while (t--) {
        int k;
        cin >> k;
        vector<int> arr;
        string input;
        cin.ignore();
        getline(cin, input);
        stringstream ss(input);
        int number;
        while (ss >> number) {
            arr.push_back(number);
        }
        Solution ob;
        int res = ob.binarysearch(arr, k);
        cout << res << endl;
        cout << "~" << endl;
    }
    return 0;
}

// } Driver Code Ends