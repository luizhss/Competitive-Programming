/*
	Dijkstra algorithm (Shortest Path)
	
	Given a graph and a starting vertex s. Find the length
	and the path to vertex s.

	Complexity:
		dijkstra() -> O(ElogV)
		restore_path() -> O(V)
*/

int n;
std::vector<std::pair<int,int>> graph[MAX];
int path[MAX];
int dist[MAX];

void dijkstra(int s){
    for(int i = 0; i < n; i++) dist[i] = path[i] = INT_MAX;
    dist[s] = 0; path[s] = -1;
    std::priority_queue<std::pair<int,int>> q;
    q.push({0, s});
    std::bitset<MAX> vis(0);
    while(!q.empty()){
        int now = q.top().second; q.pop();
        if(vis[now]) continue;
        vis[now] = 1;
        for(auto v : graph[now]){
            if(dist[v.second] > dist[now] + v.first){
                dist[v.second] = dist[now] + v.first;
                path[v.second] = now;
                q.push({-dist[v.second], v.second});
            }
        }

    }
}

std::vector<int> restore_path(int s, int t) {
    std::vector<int> ret;

    for (int v = t; v != s; v = path[v])
        ret.push_back(v);
    ret.push_back(s);

    std::reverse(ret.begin(), ret.end());
    return ret;
}