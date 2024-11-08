//{ Driver Code Starts
//Initial template for C++

#include<bits/stdc++.h>
using namespace std;

int Search(vector<int> ,int );

//User code will be pasted here

int main(){

    int t;
    cin >> t;

    while(t--){
        int n;
        cin >> n;
        
        vector<int> vec(n);
        
        for(int i =0;i<n;i++) 
            cin >> vec[i];
        
        int target;
        cin >> target;
        
        cout << Search(vec,target) << "\n";
         
    
cout << "~" << "\n";
}
}
// } Driver Code Ends

int merge(int i1, int i2) {
    if (i1 == -1 && i2 == -1) {
        return -1;
    }
    
    if (i1 != -1) {
        return i1;
    }
    
    return i2;
}

int search(std::vector<int>& v, int k, int p, int r) {
    int q = (p + r) / 2;
    
    // Caso in cui l'elemento e' in posizione q
    if (v[q] == k) {
        return q;
    }
    
    // Caso in cui l'array ha un solo elemento e v[q] != k
    if (r - p == 0) {
        return -1;  
    }
    
    // Caso in cui l'array ha due elementi e v[q + 1] == k
    if (r - p == 1 && v[q + 1] == k) {
        return q + 1;
    }
    
    // Caso in cui l'array ha due elementi, v[q] != k e 
    // v[q + 1] != k
    if (r - p == 1) {
        return -1;
    }
    
    // Se v ha almeno tre elementi, v[q] != k, sto nella parte
    // crescente, e la chiave e' a sinistra nella parte crescente
    if (v[q] > v[p] && v[q] < v[r] && k < v[q]) {
        // ricorri a sinistra
        return search(v, k, p, q - 1);
    }
    
    // Se v ha almeno tre elementi, v[q] != k, sto nella parte 
    // crescente, e la chiave e' a destra nella parte crescente
    if (v[q] > v[p] && v[q] < v[r] && k > v[q]) {
        // ricorri a destra
        return search(v, k, q + 1, r);
    }
    
    // Se v ha almeno tre elemeti, v[q] != k e sto nella parte 
    // ruotata, cerca a sinistra e a destra della parte ruotata, e 
    // fai il merge dei risultati
    return merge(search(v, k, p, q), search(v, k, q + 1 , r));
    // L'idea e' che in ciascuna delle ricerche o ottengo un 
    // sottovettore ordinato, quindi riconduco il problema ai casi 
    // precedenti, o ottengo un sottovettore ruotato, quindi
    // continuo a scomporre fino a ricondurmi al caso di vettori
    // ordinati o ai casi base.
}

//User function template for C++

// vec : given vector of elements
// K : given value whose index we need to find 
int Search(vector<int> vec, int K) {
    //code here
    return search(vec, K, 0, vec.size() - 1);
}