/*
	Beautifil Mountains - 2020 LA Regional

	Prerequisites: RMQ data structure
*/

/*
	Beautifil Mountains - 2020 LA Regional

	Prerequisites: RMQ data structure
*/

#include <bits/stdc++.h>
 
using namespace std;
 
#define FOR(i, a) for(int i = 0; i < (int) a; i++)
#define PB push_back
#define all(x) x.begin(), x.end()
#define rall(x) x.rbegin(), x.rend()
#define F first
#define S second
 
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;
 
const int MAX = 1e5+7, INF = 1e9+7;
 
template <typename T>
struct sparse_table{
	vector<vector<T>> v;
	vector<T> log;
	int n, k;
	bool maxi;

	sparse_table(vector<T>& arr, bool maxi): maxi(maxi){
		n = arr.size()+7; k = 0;
		v.resize(n);

		// Only for min/max queries
		log.resize(n+1, 0);
		log[1] = 0;
		for(int i = 2; i <= n; i++)
			log[i] = log[i/2] + 1;

		while((1<<k) <= n)	k++;
		for(int i = 0; i < n; i++){
			v[i].resize(k);
			v[i][0] = arr[i];
		}

		for(int j = 1; j <= k; j++){
			for(int i = 0; i + (1<<j) <= n; i++)
				if(maxi) v[i][j] = max(v[i][j-1], v[i+(1<<(j-1))][j-1]);
				else     v[i][j] = min(v[i][j-1], v[i+(1<<(j-1))][j-1]);
		}
	}

	T query(int l, int r){
		int j = log[r-l+1];
		if(maxi) 
			return max(v[l][j], v[r-(1<<j)+1][j]);
		return min(v[l][j], v[r-(1<<j)+1][j]);
	}
};
 
int main(){
	ios::sync_with_stdio(false); cin.tie(0);
 
	int n; cin >> n;
	vi v(n); FOR(i, n) cin >> v[i];
	vi R(n, n), L(n, -1);
 
	stack<int> h;
	for(int i = n-1; i >= 0; i--){
		if(v[i] == -1) continue;
 
		while(!h.empty() && v[i] <= v[h.top()])
			h.pop();
 
		if(!h.empty()){
			R[i] = h.top();
		}
 
		h.push(i);
	}
 
	while(!h.empty()) h.pop();
 
	for(int i = 0; i < (int) n; i++){
		if(v[i] == -1) continue;
 
		while(!h.empty() && v[i] <= v[h.top()])
			h.pop();
 
		if(!h.empty()){
			L[i] = h.top();
		}
 
		h.push(i);
	}
 
	sparse_table<int> sL(L, true);
	sparse_table<int> sR(R, false);
 
	for(int i = 3; i <= n; i++){
		bool ok = true;
		for(int j = 0; j < n; j+=i){
			int l = j, r = min(j+i-1, n-1);
			int lq = sL.query(l, r), rq = sR.query(l, r);
			if(r-l+1 < 3 || lq >= rq || lq >= r-1 || rq <= l+1){
				ok = false;
				break;
			}
		}
		if(ok){
			cout << "Y\n";
			return 0;
		}
	}
 
	cout << "N\n";
 
	return 0;
}