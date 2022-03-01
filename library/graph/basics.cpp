/*	
	Basic graphs algorithms
*/

vi graph[MAX];
bitset<MAX> vis;

/*
	Graph Transversal Algorithm
*/
void dfs(int s){
	vis[s] = 1;
	for(auto& v: graph[s]){
		if(!vis[v]) dfs(v);
	}
}

void bfs(int s){
	std::queue<int> q;
	q.push(s);
	vis.reset();
	while(!q.empty()){
		int v = q.front(); q.pop();
		if(vis[v]) continue;
		vis[v] = 1;
		for(auto& c : graph[v]){
			if(!vis[c]) q.push(c);
		} 
	}
}

/*
	Finding cycles
*/
std::vector<char> color;
std::vector<int> cycle;
int cycle_start, cycle_end;

// for directed graphs
bool dfs(int s, int p=-1) {
    color[s] = 1;
    for(auto& v : graph[s]) {
    	if(v == p) continue;
    	if(color[v] == 1) {
            cycle_end = s;
            cycle_start = v;
            return true;
        }
        parent[v] = s;
        if(dfs(v)) return true;
        //if(dfs(v, s)) return true; // undirected graph
    }
    color[s] = 2;
    return false;
}

// n -> number of vertices
bool find_cycle(int n) {
    color.assign(n, 0);
    parent.assign(n, -1);
    cycle_start = -1;

    for (int v = 0; v < n; v++) {
        if (color[v] == 0 && dfs(v)){
        	break; // found cycle
        }
    }

    if (cycle_start == -1) 
    	return false; // no cycle

    cycle.push_back(cycle_start);
    for (int v = cycle_end; v != cycle_start; v = parent[v])
        cycle.push_back(v);
    cycle.push_back(cycle_start);
    std::reverse(cycle.begin(), cycle.end());

    return true;
}
