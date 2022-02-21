/*
    Halting Wolf - 2020 LA Regional

    Prerequisites: Max Flow
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
 
struct FlowEdge {
    int v, u;
    long long cap, flow = 0;
    FlowEdge(int v, int u, long long cap) 
    : v(v), u(u), cap(cap) {}
};

struct Dinic {
    const long long flow_inf = MAX;
    std::vector<FlowEdge> edges;
    std::vector<vector<int>> adj;
    int n, m = 0;
    int s, t;
    vector<int> level, ptr;
    queue<int> q;

    Dinic(int n, int s, int t) : n(n), s(s), t(t) {
        adj.resize(n);
        level.resize(n);
        ptr.resize(n);
    }

    void add_edge(int v, int u, long long cap) {
        edges.emplace_back(v, u, cap);
        edges.emplace_back(u, v, 0);
        adj[v].push_back(m);
        adj[u].push_back(m + 1);
        m += 2;
    }

    bool bfs() {
        while (!q.empty()) {
            int v = q.front();
            q.pop();
            for (int id : adj[v]) {
                if (edges[id].cap - edges[id].flow < 1)
                    continue;
                if (level[edges[id].u] != -1)
                    continue;
                level[edges[id].u] = level[v] + 1;
                q.push(edges[id].u);
            }
        }
        return level[t] != -1;
    }

    long long dfs(int v, long long pushed) {
        if (!pushed || v == t) return pushed;
        for (int& cid = ptr[v]; cid < (int)adj[v].size(); cid++) {
            int id = adj[v][cid];
            int u = edges[id].u;
            if (level[v]+1 != level[u] 
                || edges[id].cap-edges[id].flow < 1)
                continue;
            long long tr = dfs(u, min(pushed, edges[id].cap-edges[id].flow));
            if (tr == 0)
                continue;
            edges[id].flow += tr;
            edges[id ^ 1].flow -= tr;
            return tr;
        }
        return 0;
    }

    long long flow() {
        long long f = 0;
        while (true) {
            std::fill(level.begin(), level.end(), -1);
            level[s] = 0;
            q.push(s);
            if (!bfs())
                break;
            std::fill(ptr.begin(), ptr.end(), 0);
            while (long long pushed = dfs(s, flow_inf)) {
                f += pushed;
            }
        }
        return f;
    }
};
 
int main(){
	ios::sync_with_stdio(false); cin.tie(0);
 
	int n; cin >> n;
	Dinic flow = Dinic(n+1, 0, n);
 
	FOR(i, n){
		string t; cin >> t;
		if(t == "*"){
			int to; cin >> to;
			to--;
			if(to == 0)
				flow.add_edge(i, n, MAX);
			else
				flow.add_edge(i, to, MAX);
				
		}else{
			int k = stoi(t, nullptr, 10);
 
			vector<int> cnt(n, 0);
			FOR(j, k){
				int x; cin >> x;
				cnt[--x]++;
			}
 
			FOR(j, n){
				if(cnt[j]){
					if(j == 0)
						flow.add_edge(i, n, cnt[j]);
					else
						flow.add_edge(i, j, cnt[j]);
					
				}
			}
		}
	}
 
	int ret = flow.flow();
	if(ret >= MAX) cout << "*\n";
	else cout << ret + 1 << '\n';
 
	return 0;
}