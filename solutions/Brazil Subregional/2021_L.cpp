/*
	Listing Passwords - 2021 Brazil Subregional

    prerequires: Sparse Table concept and DSU
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

const int MAX = 3e5+7;
const int MOD = 1e9+7;

struct DSU{
	std::vector<int> parent, ranks;

	DSU(int n){
		parent.resize(n+1);
		ranks.resize(n+1);
		for(int i = 0; i < n; i++)
			ranks[i] = 1, parent[i] = i;
	}

	int find(int x){
		if(x == parent[x]) return x;
		return parent[x] = find(parent[x]);
	}

	void join(int a, int b){
		a = find(a); b = find(b);
		if(a != b){
			if(ranks[a] > ranks[b]) std::swap(a, b);
			parent[a] = b;
			ranks[b] += ranks[a];
		}
	}
};

int flip(int i, int n){
	return 2*n-i-1;
}

int bin_exp(int x, int p){
	int ret = 1;
	while(p){
		if(p&1)
			ret = 1LL * ret * x % MOD;
		p >>= 1;
		x = 1LL * x * x % MOD;
	}
	return ret;
}

int main(){
	ios::sync_with_stdio(false); cin.tie(0);

	int n, m; cin >> n >> m;
	string s; cin >> s;

	vector<DSU> d(20, DSU(2*n));
	FOR(i, n) d[0].join(i, flip(i, n));

	FOR(i, m){
		int a, b; cin >> a >> b;
		if(a==b) continue;
		a--; b--;

		int c = flip(b, n);
		int k = b-a+1, sum = 0;
		for(int j = 0; (1<<j) <= k; j++){
			if((1<<j)&k){
				d[j].join(a+sum, c+sum);
				sum += (1<<j);
			}
		}
	}

	for(int j = 19; j > 0; j--){
		if((1<<j) > n) continue;
		vi vis(2*n, -1);
		int k = (1<<(j-1));
		for(int i = 0; i + (1<<j) <= n; i++){
			int p = d[j].find(i);
			if(vis[p] != -1){
				int x = vis[p];
				d[j-1].join(x, i);
				d[j-1].join(x+k, i+k);
			}
			vis[p] = i;

			p = d[j].find(i+n);
			if(vis[p] != -1){
				int x = vis[p];
				d[j-1].join(x, i+n);
				d[j-1].join(x+k, i+n+k);
			}
			vis[p] = i+n;
		}
	}

	int ans = 0;
	vi v(2*n, -1);
	FOR(i, n){
		int x = d[0].find(i);
		if(v[x] != -1){
			if(v[x] > 0){
				if(s[i] != '?' && v[x] != s[i]-'0'+1){
					cout << "0\n"; return 0;
				}
			}else{
				if(s[i] != '?') 
					v[x] = (s[i]-'0')+1;
			}
		}else{
			if(s[i] == '?') v[x] = 0;
			else v[x] = (s[i]-'0')+1;
		}
	}

	FOR(i, 2*n) ans += (v[i] == 0);
	cout << bin_exp(2, ans) << '\n';

	return 0;
}
