/*
	Fenwick Tree 2D (Binary Indexed Tree)
	
	Efficiently update and calculates prefix of a reversible function f.
	This implementation is one-based indexing.

	Operations:
		get(x, y) -> query for f in range [1, x][1, y]
		update(i, x) -> updates i-th element by x
	
	Complexity:
		operator[](x) -> O(log(n*m))
		update(i, x) -> O(log(n*m))
*/

template <typename T>
struct FenwickTree2d{
	int size;
	std::vector<vector<T>> v;

	FenwickTree2d(int n){
		size = n;
		v.assign(size+1, vector<T>(size+1, 0)); 
	}

	T query(int x, int y){
		T ans = 0;
		for(int i=x; i; i-=(i&(-i)))
			for(int j=y; j; j-=(j&(-j)))
				ans += v[i][j];
		return ans;
	}

	void update(int x, int y, T val){
		for(int i=x; i<=size; i+=(i&(-i))){
			for(int j=y; j<=size; j+=(j&(-j)))
				v[i][j] += val;
		}
	}
};