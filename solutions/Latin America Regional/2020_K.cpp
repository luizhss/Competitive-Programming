/*
    Keylogger - 2020 LA Regional
*/

/*
    Keylogger - 2020 LA Regional
*/

#include <bits/stdc++.h>
 
using namespace std;
 
#define FOR(i, n) for(int i = 0; i < (int) n; i++)
#define PB push_back
#define all(x) x.begin(), x.end()
#define rall(x) x.rbegin(), x.rend()
#define F first
#define S second
 
typedef long long ll;
typedef vector<int> vi;
typedef pair<int,int> pii;
 
const int MAX = 1e4+7;
const int MOD = 1e9+7;
 
int k, L, n; 
int keys[751][751];
int sequence[MAX];

template <typename T>
struct FenwickTree{
    int size;
    std::vector<T> v;

    FenwickTree(int n){
        size = n;
        v.assign(size+1, 0); 
    }

    FenwickTree(vector<T> arr){
        size = arr.size();
        v.assign(size+1, 0);
        for(int i = 1; i <= size; i++){
            v[i] += arr[i-1];
            if(i + (i&(-i)) <= size){
                v[i + (i&(-i))] += arr[i-1]; 
            }
        }
    }

    T operator[](int i){
        T ans = 0;
        for(; i; i-=(i&(-i))){
            ans = (ans + v[i]) % MOD;
            if(ans < 0) ans += MOD;
        }
        return ans;
    }

    void update(int i, T x){
        for(; i <= size; i+=(i&(-i))){
            v[i] = (v[i] + x) % MOD;
            if(v[i] < 0) v[i] += MOD;
        }
    }
};
 
int binarySearchLower(int i, ll x){
    int l = -1, r = k;
    while(r > l+1){
        int m = (r+l)/2;
        if(x <= keys[i][m]) r = m;
        else l = m;
    }
    return r;
}
 
int binarySearchUpper(int i, ll x){
    int l = -1, r = k;
    while(r > l+1){
        int m = (r+l)/2;
        if(x < keys[i][m]) r = m;
        else l = m;
    }
    return l;
}
 
int main(){
    ios::sync_with_stdio(false); cin.tie(0);
 
    cin >> k >> L;
    FOR(i, k) FOR(j, k) cin >> keys[i][j];
    cin >> n;
    FOR(i, n-1) cin >> sequence[i];
 
    FenwickTree possibles = FenwickTree<ll>(k);
    possibles.update(1, 1);
 
    FOR(j, n-1){
        int p = sequence[j];
        FenwickTree aux = FenwickTree<ll>(k);
        for(int i = 0; i < k; i++){
            ll cur = possibles[i+1];
            if(cur){
                int l = binarySearchLower(i, p - L);
                int r = binarySearchUpper(i, p + L);
 
                if(l <= r){
                    aux.update(l+1,  cur);
                    aux.update(r+2, -cur);
                }
            }
        }
 
        possibles = aux;
    }
 
    ll ans = 0;
    for(int i = 0; i < k; i++) 
        ans = (1LL*ans + possibles[i+1]) % MOD;
 
    cout << ans << '\n';
 
    return 0;
}