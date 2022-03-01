/*
	Disjoint set union with bipartide sets
	
	Stores collection of disjoint sets. Each element only links
	with another of different color.

	Operations:
		find(x) -> get the set representative member
		join(x, y) -> merge two sets
	
	Complexity:
		find() -> O(a(n)) ~ almost constant
		join() -> O(a(n)) ~ almost constant

*/

struct DSU{
	std::vector<int> par, rnk, col;
 
	DSU(int n){
		par.resize(n+1);
		col.resize(n+1);
		rnk.resize(n+1);
		for(int i = 0; i < n; i++)
			rnk[i] = 1, col[i] = 0, par[i] = i;
	}
 
	pii find(int x){
		if(par[x] == x)
			return {x, 0};
		pii p = find(par[x]);
		par[x] = p.F;
		col[x] = (col[x] + p.S) % 2;
		return {p.F, col[x]};
	}
 
	void join(int a, int b){
		pii pa = find(a), pb = find(b);
		if(rnk[pa.F] > rnk[pb.F])
			std::swap(pa, pb);
		
		par[pa.F] = pb.F;
		col[pa.F] = (1 + pa.S + pb.S) % 2;	
		rnk[pb.F] += rnk[pa.F];
	}
};