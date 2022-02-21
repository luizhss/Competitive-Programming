/*
	Fabricating Sculptures - 2019 LA Regional
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
 
const int MAX = 5007;
const int MOD = 1e9+7;
const int INF = 0x3f3f3f3f;
 
int dp[MAX][MAX];
int p1[MAX][MAX], p2[MAX][MAX];
 
int solve(int s, int b){
	int i = min(s, b);
 
	if(dp[s][b] != -1) return dp[s][b];
	if(s == 1 || b == 0){
		p1[s][b] = 1;
		p2[s][b] = 0;
		return dp[s][b] = 1;
	}
 
	if(s <= b){
		solve(s-1, b);
		int ret = solve(s, b-s);
		p1[s][b] = ((ll) p1[s-1][b] + ret) % MOD;
		p2[s][b] = ((ll) p2[s-1][b] + 1LL * (s-1) * ret) % MOD;
	}else{
		solve(i, b);
	}
 
	int ret = (1LL * s * p1[i][b]) % MOD;
	ret = (ret - p2[i][b] + MOD) % MOD;
	return dp[s][b] = ret;
}
 
int main(){
	ios::sync_with_stdio(false); cin.tie(0);
 
	int s, b; cin >> s >> b;
	FOR(i, MAX) FOR(j, MAX)
		dp[i][j] = p1[i][j] = p2[i][j] = -1;
	
	cout << solve(s, b-s) << '\n';
 
	return 0;
}