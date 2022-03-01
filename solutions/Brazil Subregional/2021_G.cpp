/*
    Getting in Shape - 2021 Brazil Subregional
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

const ll MAX = 1e15+7;
const int INF = 1e5+7;

int sz;
ll fib[100]; 

bool solve(ll n, vi& v, int last){
 
    if(n == 1) return true;
 
    string ans = "*";
    for(int j = last; j > 0; j--){
        if(n%fib[j] == 0){
            v.PB(j);
            if(solve(n/fib[j], v, j))
                return true;
            v.pop_back();
        }
    }
 
    return false;
}

int main(){
    ios::sync_with_stdio(false); cin.tie(0);


    ll n; cin >> n;
    
    fib[0] = 1; fib[1] = 2;
    for(sz = 2; fib[sz-1] <= n; sz++){
        fib[sz] = fib[sz-1] + fib[sz-2];
    }

    vi ans;
    if(solve(n, ans, sz-1)){
        for(auto& x : ans)
            cout << string(x, 'A') << 'B';
        cout << '\n';
    }else{
        cout << "IMPOSSIBLE\n";
    }

    return 0;
}