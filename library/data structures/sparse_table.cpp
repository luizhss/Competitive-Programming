/*
	Sparse Table
	
	Answer min/max range queries in O(1). Others range queries
	in O(log(n)). 

	Operations:
		find(x) -> get the set representative member
		join(x, y) -> merge two sets
	
	Complexity:
		find() -> O(a(n)) ~ almost constant
		join() -> O(a(n)) ~ almost constant

*/

template <typename T>
struct sparse_table{
	vector<vector<T>> v;
	vector<T> log;
	int n, k;

	sparse_table(vector<T>& arr){
		n = arr.size()+7; k = 0;
		v.resize(n);

		// Only for min/max queries
		log.resize(n+1, 0);
		log[1] = 0;
		for(int i = 2; i <= n; i++)
			log[i] = log[i/2] + 1;

		while((1<<k) <= n) k++;
		for(int i = 0; i < n; i++){
			v[i].resize(k);
			v[i][0] = arr[i];
		}

		for(int j = 1; j <= k; j++){
			for(int i = 0; i + (1<<j) <= n; i++)
				v[i][j] = min(v[i][j-1], v[i+(1<<(j-1))][j-1]);
				// v[i][j] = v[i][j-1] + v[i+(1<<(j-1))][j-1];
		}
	}

	T min_query(int l, int r){
		int j = log[r-l+1];
		return min(v[l][j], v[r-(1<<j)+1][j]);
	}

	T sum_query(int l, int r){
		T sum = 0;
		for(int j = k; j >= 0; j--){
			if((1<<j) <= r-l+1){
				sum += v[l][j];
				l += (1<<j);
			}
		}
		return sum;
	}
};