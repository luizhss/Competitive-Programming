/*
    Kill the Werewolf - 2016 LA Regional

    Prerequisites: Max Flow
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

struct FlowEdge {
    int v, u;
    long long cap, flow = 0;
    FlowEdge(int v, int u, long long cap) : v(v), u(u), cap(cap) {}
};

struct Dinic {
    const long long flow_inf = 1e18;
    vector<FlowEdge> edges;
    vector<vector<int>> adj;
    int n, m = 0;
    int src, snk;
    vector<int> level, ptr;
    queue<int> q;

    Dinic(int n, int s, int t) : n(n), src(s), snk(t) {
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
        return level[snk] != -1;
    }

    long long dfs(int v, long long pushed) {
        if (!pushed || v == snk) return pushed;
        for (int& cid = ptr[v]; cid < (int)adj[v].size(); cid++) {
            int id = adj[v][cid];
            int u = edges[id].u;
            if (level[v] + 1 != level[u] || edges[id].cap - edges[id].flow < 1)
                continue;
            long long tr = dfs(u, min(pushed, edges[id].cap - edges[id].flow));
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
            fill(level.begin(), level.end(), -1);
            level[src] = 0;
            q.push(src);
            if (!bfs()) break;
            fill(ptr.begin(), ptr.end(), 0);
            while (long long pushed = dfs(src, flow_inf)) {
                f += pushed;
            }
        }
        return f;
    }
};

int e[57][2];

int main(){
	ios::sync_with_stdio(false); cin.tie(0);

	int n; cin >> n;
	FOR(i, n){
		cin >> e[i][0] >> e[i][1];
		e[i][0]--; e[i][1]--;
	}

	int ans = 0;
	int src = 2*n, snk = 2*n+1;
	FOR(i, n){
		Dinic d = Dinic(2*n+2, src, snk);
		int m = 0;
		FOR(j, n) {
			if(i == j) continue;
			if(e[j][0] == i || e[j][1] == i){
				m++; continue;
			}
			d.add_edge(src, j, 1);
			d.add_edge(j, e[j][0]+n, 1);
			d.add_edge(j, e[j][1]+n, 1);
		}

		FOR(j, n){
			if(i == j) continue;
			if(j == e[i][0] || j == e[i][1])
				d.add_edge(j+n, snk, max(m-2, 0));
			else
				d.add_edge(j+n, snk, max(m-1, 0)); 
		}

		int ret = d.flow();
		if(ret < n-m-1) ans++;
	}

	cout << ans << '\n';

	return 0;
}