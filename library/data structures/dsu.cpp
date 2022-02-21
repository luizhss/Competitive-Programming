/*
	Disjoint set union
	
	Stores collection of disjoint sets.

	Operations:
		find(x) -> get the set representative member
		join(x, y) -> merge two sets
	
	Complexity:
		find() -> O(a(n)) ~ almost constant
		join() -> O(a(n)) ~ almost constant

*/

const int MAX = 1e5+7;

struct DSU{
	std::vector<int> parent, ranks;

	DSU(int n){
		parent.resize(n+1);
		ranks.resize(n+1);
		for(int i = 0; i < n; i++)
			ranks[i] = 1, parent[i] = i;
	}

	int find(int x){
		if(x == parent[x]) return x;
		return parent[x] = find(parent[x]);
	}

	void join(int a, int b){
		a = find(a); b = find(b);
		if(a != b){
			if(ranks[a] > ranks[b]) std::swap(a, b);
			parent[a] = b;
			ranks[b] += ranks[a];
		}
	}
};