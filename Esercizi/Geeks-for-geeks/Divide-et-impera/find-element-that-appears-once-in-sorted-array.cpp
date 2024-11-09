//{ Driver Code Starts
// Driver code

#include<bits/stdc++.h>
using namespace std;


// } Driver Code Ends
class Solution
{
    int merge(int x1, int x2) {
        if (x1 == -1 && x2 == -1) {
            return -1;
        }
        
        if (x1 != -1) {
            return x1;
        }
        
        return x2;
    }
    
    int findElemThatAppearsOnce(int v[], int p, int r, int n) {
        // Se durante la ricerca esco fuori dai bordi
        if (p < 0 || r > n - 1 || p > n - 1 || r < 0) {
            return -1;
        }
        
        // Se la sottosequenza e' vuota
        if (r - p < 0) {
            return -1;
        }
        
        // Se la sottosequenza ha un solo elemento, non e' ai bordi
        // e l'elemento che contiene e' diverso da quelli circostanti
        if (r - p == 0 && p > 0 && p < n - 1  && 
            v[p] != v[p - 1] && v[p] != v[p + 1]) 
        {
            // ritorna l'elemento
            return v[p];
        }
        
        // Se la sottosequenza ha un solo elemento, non e' ai bordi
        // e l'elemento che contiene e' uguale ad uno di quelli 
        // circostanti
        if (r - p == 0 && p > 0 && p < n - 1) {
            // l'elemento cercato non esiste
            return -1;
        }
        
        // Se la sottosequenza ha un solo elemento, e' al bordo destro
        // e l'elemento e' diverso da quello alla sua sinistra
        if (r - p == 0 & p > 0 && v[p] != v[p - 1]) {
            // ritorna l'elemento
            return v[p];
        }
        
        // Se la sottosequenza ha un solo elemento, e' al bordo destro
        // e l'elemento e' uguale a quello alla sua sinistra.
        if (r - p == 0 && p > 0) {
            // l'elemento cercato non esiste
            return -1;
        }
        
        // Se la sottosequenza ha un solo elemento, e' al bordo sinistro
        // e l'elemento e' diverso da quello alla sua destra
        if (r - p == 0 && p < n - 1 && v[p] != v[p + 1]) {
            // ritorna l'elemento
            return v[p];
        }
        
        // Se la sottosequenza ha un solo elemento, e' al bordo sinistro
        // e l'elemento e' uguale a quello alla sua destra
        if (r - p == 0) {
            // l'elemento cercato non esiste
            return -1;
        }
        
        // Se la sottosequenza ha soli due elementi
        if (r - p == 1) {
            // unisci le soluzioni delle ricerche nelle sottosequenze
            // costituite dal solo elemento sinistro e destro 
            // rispettivamente
            return merge(findElemThatAppearsOnce(v, p, p, n),
                findElemThatAppearsOnce(v, r, r, n));
        }
        
        // Considero l'elemento di indice medio
        int q = (p + r) / 2;
        
        // Se la sottosequenza contiene almeno tre elementi e l'elemento
        // centrale e' diverso da quelli circostanti
        if (v[q] != v[q - 1] && v[q] != v[q + 1]) {
            // ritorna l'elemento centrale
            return v[q];    
        }
        
        // Se la sottosequenza contiene almeno tre elementi e l'elemento
        // centrale e' uguale a quello sinistro
        if (v[q] == v[q - 1]) {
            // unisco le soluzioni delle ricerche sottosinistre e destre
            // escludenti gli elementi confrontati
            return merge(findElemThatAppearsOnce(v, p, q - 2, n),
                findElemThatAppearsOnce(v, q + 1, r, n)); 
        }
        
        // Se la sottosequenza contiene almeno tre elementi e l'elemento
        // centrale e' uguale a quello destro
        if (v[q] == v[q + 1]) {
            // unisco le soluzioni delle ricerche sottosinistre e destre
            // escludenti gli elementi confrontati
            return merge(findElemThatAppearsOnce(v, p, q - 1, n), 
                findElemThatAppearsOnce(v, q + 2, r, n));
        }
    }    
    
  public:
    int findOnce(int arr[], int n)
    {
        //code here.
        if (n == 1) {
            return arr[0];
        }
        
        return findElemThatAppearsOnce(arr, 0, n - 1, n);
    }
};

//{ Driver Code Starts.

int main()
{
    int t;
    cin >> t;

    while (t--)
    {
        int n;
        cin >> n;
        int A[n];
        for(int i = 0;i < n;i++)
        {
            cin>>A[i];
        }
        
        Solution ob;
        
        int res = ob.findOnce(A,n);
        cout << res << endl;
    
cout << "~" << "\n";
}
    
    return 0;
}
// } Driver Code Ends