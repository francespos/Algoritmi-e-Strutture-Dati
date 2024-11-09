//{ Driver Code Starts
#include <bits/stdc++.h>
using namespace std;

// } Driver Code Ends

#include <cmath>
class Solution {
  public:
  // Alcune considerazioni. 
  // Anzitutto, sarebbe opportuno passare come argomento oggetti di
  // tipo std::string_view, al fine di evitare l'overhead dovuto 
  // alla creazione delle stringhe.
  // Poi, osserviamo che la complessita' è pari al tempo richiesto per
  // convertire la stringa più lunga, cioè Theta(n), supposto che le
  // operazioni di elevamento a potenza, di addizione e moltiplicazione
  // abbiano complessita' Theta(1).
  // Una procedura più accurata per il calcolo della complessita' tiene
  // conto del fatto che, realisticamente e per esponenti abbastanza 
  // grandi, la complessita' dell'elevamento a potenza e' O(log n), 
  // quindi la soluzione del problema avrebbe complessita' O(nlogn).
    long long powOfTwo(int exp) {
        if (exp == 0) {
            return 1;
        }
        
        if (exp % 2 == 0) {
            return powOfTwo(exp/2) * powOfTwo(exp/2);
        }
        
        return 2 * powOfTwo(exp - 1);;
    }
  
    long long convertToDecimal(const std::string& s, int pos) {
        if (pos == s.size()) {
            return 0;
        }
        
        auto digit = s[s.size() - pos - 1] - '0';
        
        return digit * powOfTwo(pos) + 
            convertToDecimal(s, pos + 1); 
    }
    
    long long convertToDecimal(const std::string& s) {
        return convertToDecimal(s, 0);
    }
  
    long long karatsubaAlgo(string A, string B) {
        return convertToDecimal(A) * convertToDecimal(B);
    }
};

//{ Driver Code Starts.
int main() {
    int t;
    cin >> t;
    while (t--) {
        string A,B;

        cin>>A>>B;

        Solution ob;
        cout << ob.karatsubaAlgo(A,B) << endl;
    
cout << "~" << "\n";
}
    return 0;
}
// } Driver Code Ends