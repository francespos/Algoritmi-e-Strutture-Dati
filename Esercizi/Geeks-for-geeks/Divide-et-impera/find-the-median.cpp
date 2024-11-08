//{ Driver Code Starts
#include<bits/stdc++.h>
using namespace std;

// } Driver Code Ends

#include <algorithm>
class Solution
{
public:
	public:
		int find_median(vector<int> v)
		{
		    auto len = v.size();
		    std::sort(v.begin(), v.begin() + len);
		    
		    int q = (len - 1) / 2;
		    
		    if (len % 2 == 1) {
		        return v[q];
		    }
		    
		    return (v[q] + v[q + 1]) / 2;
		}
};

//{ Driver Code Starts.
int main(){
    int T;
    cin >> T;
    while(T--)
    {
    	int n; 
    	cin >> n;
    	vector<int> v(n);
    	for(int i = 0; i < n; i++)
    		cin>>v[i];
    	Solution ob;
    	int ans = ob.find_median(v);
    	cout << ans <<"\n";
    
cout << "~" << "\n";
}
	return 0;
}

// } Driver ACode Ends