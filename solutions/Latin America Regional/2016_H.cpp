/*
	Hotel Rewards - 2016 LA Regional
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

const int MAX = 1e5+7;

int main(){
	ios::sync_with_stdio(false); cin.tie(0);

	int n, k; cin >> n >> k;
	vi v(n); FOR(i, n) cin >> v[i];

	int sum = accumulate(all(v), 0);

	priority_queue<int> q;
	for(int i = k; i < n; i++){
		if(i - ((int) q.size())*(k+1) == k){
			q.push(-v[i]);
		}else if(!q.empty() && v[i] > -q.top()){
			q.pop(); q.push(-v[i]);
		}
	}

	int less = 0;
	while(!q.empty()){
		less -= q.top(); q.pop();
	}

	cout << sum - less << '\n';

	return 0;
}