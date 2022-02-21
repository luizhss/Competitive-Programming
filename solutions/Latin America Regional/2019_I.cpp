/*
	Improve SPAM - 2019 LA Regional
*/

#include <bits/stdc++.h>

using namespace std;

#define FOR(i, n) for(int i = 0; i < (int) n; i++)
#define all(v) v.begin(), v.end()
#define PB push_back
#define F first
#define S second

typedef long long ll;
typedef vector<int> vi;
typedef vector<ll> vl;
typedef pair<int,int> pii;

const ll MOD = 1e9+7;
const int MAX = 2007;

int n, l; 
vi graph[MAX];
int mails[MAX], child[MAX];

void dfs(int i, int p=-1){
	for(auto& v : graph[i]){
		if(v < l){
			if(mails[v] == 0)
				dfs(v);
			mails[i] = ( (ll) mails[i] + mails[v]) % MOD;
		}else{
			child[v] = 1;
			mails[i]++;
			mails[i] %= MOD;
		}
	}
}

int main(){
	ios::sync_with_stdio(false); cin.tie(0);

	cin >> n >> l;
	FOR(i, l){
		int k; cin >> k;
		FOR(j, k){
			int x; cin >> x; x--;
			graph[i].PB(x);
		}
	}

	dfs(0);

	int c = 0;
	for(int i = l; i < n; i++) c+= (child[i]);

	cout << mails[0] << ' ' << c << '\n';

	return 0;
}