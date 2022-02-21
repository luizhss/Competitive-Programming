/*
	Back to the Future - 2016 LA Regional
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

int n, m, A, B;
set<int> graph[MAX];
bitset<MAX> vis;

void check(vi& root, set<int>& cur){
	queue<int> q;
	for(auto& r: root) q.push(r);
	int& C = cur.size();
	while(!q.empty()){
		int x = q.front(); q.pop();
		if(vis[x]) continue;

		int G = graph[x].size();
		if(G < A || (C-G-1) < B){
			vis[x] = 1;
			for(auto& d: graph[x]){
				graph[d].erase(x);
				q.push(d);
			}
			cur.erase(x);
		}
	}
}

int main(){
	ios::sync_with_stdio(false); cin.tie(0);
	
	cin >> n >> m >> A >> B;
	FOR(i, m){
		int x, y; cin >> x >> y;
		x--; y--;
		graph[x].insert(y);
		graph[y].insert(x);
	}

	set<int> cur;
	FOR(i, n) cur.insert(i);

	bool ok = true;
	do{
		ok = false;
		vi root;
		int C = cur.size();
		for(auto& x : cur){
			int G = graph[x].size();
			if(G < A || (C-G-1) < B){
				root.PB(x);
				ok = true;
			}
		}
		check(root, cur);
	}while(ok);

	cout << cur.size() << '\n';

	return 0;
}
