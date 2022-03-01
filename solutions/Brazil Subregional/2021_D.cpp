/*
    Dividing the Kingdom - 2021 Brazil Subregional

    requires: DSU
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

const int MAX = 5e5+7;

struct DSU{
	std::vector<int> par, rnk, len;

	DSU(int n){
		par.resize(n+1);
		len.resize(n+1);
		rnk.resize(n+1);
		for(int i = 0; i < n; i++)
			rnk[i] = 1, len[i] = 0, par[i] = i;
	}

	pii find(int x){
		if(par[x] == x)
			return {x, 0};
		pii p = find(par[x]);
		par[x] = p.F;
		len[x] = (len[x] + p.S) % 2;
		return {p.F, len[x]};
	}

	void join(int a, int b){
		pii pa = find(a), pb = find(b);
		if(rnk[pa.F] > rnk[pb.F])
			std::swap(pa, pb);
		
		par[pa.F] = pb.F;
		len[pa.F] = (1 + pa.S + pb.S) % 2;	
		rnk[pb.F] += rnk[pa.F];
	}
};

struct edge{
	int u, v, w;
	bool operator<(const edge& other) const{
		return w > other.w;
	}
};

int n, m; 
vi ans;
bool solve(vector<edge>& edges, DSU& dsu){
	// check if its possible
	bool ok = false;
	map<int,int> solo;
	set<pii> btset;
	
	for(auto [u, v, ignore]: edges){
		auto [p1, c1] = dsu.find(u);
		auto [p2, c2] = dsu.find(v);

		if(p1 == p2){
			if(c1 == c2){
				if(solo.count(p1)){
					if(c1 != solo[p1]) ok = true;
				}else if(solo.empty()){
					solo[p1] = c1;
				}else{
					ok = true;
				}
			}
		}else{
			btset.insert({p1+n*c1, p2+n*c2});
		}
		if(ok) break;
	}
	if(!ok && solo.size() == 1){
		auto p = solo.begin()->F+n*solo.begin()->S;
		for(auto& [u, v]: btset){
			if(u!=p && v!=p) ok = true;
		}
	}else if(!ok && solo.empty()){
		int k = 0;
		for(auto& [u, v]: btset){
			k++;
			for(auto& [w, z]: btset){
				if(u != w && u != z && v != w && v!= z)
					ok = true;
			}
			if(k==3) break;
		}
	}
	if(ok) ans.PB(edges[0].w);

	// split edges
	for(auto [u, v, ignore] : edges){
		auto [p1, c1] = dsu.find(u);
		auto [p2, c2] = dsu.find(v);
		if(p1 == p2){
			if(c1 == c2) return false;
		}else dsu.join(u, v);
	}
	return true;
}

int main(){
	ios::sync_with_stdio(false); cin.tie(0);

	cin >> n >> m;
	DSU dsu(n);
	vector<edge> edges(m);
	FOR(i, m){
		int u, v, w; cin >> u >> v >> w;
		--u; --v;
		edges[i] = {u, v, w};
	}

	sort(all(edges));

	vector<edge> aux;
	bool ret = true;
	for(auto e: edges){
		if(aux.empty() || aux.back().w == e.w){
			aux.PB(e);
		}else{
			ret = solve(aux, dsu);
			if(!ret) break;
			aux.clear();
			aux.PB(e);
		}
	}
	if(ret) ret = solve(aux, dsu);
	if(ret) ans.PB(0);

	if(ans.empty()){
		cout << "IMPOSSIBLE\n";
	}else{
		reverse(all(ans));
		for(auto& x: ans) cout << x << '\n';
	}

	return 0;
}
