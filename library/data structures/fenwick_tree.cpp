/*
	Fenwick Tree (Binary Indexed Tree)
	
	Efficiently update and calculates prefix of a reversible function f.
	This implementation is one-based indexing.


	Operations:
		operator[](x) -> query for f in range [1, x]
		update(i, x) -> updates i-th element by x
	
	Complexity:
		(constructor) -> O(n)
		operator[](x) -> O(log(n))
		update(i, x) -> O(log(n))
*/

template <typename T>
struct FenwickTree{
	int size;
	std::vector<T> v;

	FenwickTree(int n){
		size = n;
		v.assign(size+1, 0); 
	}

	FenwickTree(vector<T> arr){
		size = arr.size();
		v.assign(size+1, 0);
		for(int i = 1; i <= size; i++){
			v[i] += arr[i-1];
			if(i + (i&(-i)) <= size){
				v[i + (i&(-i))] += arr[i-1]; 
			}
		}
	}

	T operator[](int i){
		T ans = 0;
		for(; i; i-=(i&(-i)))
			ans += v[i];
		return ans;
	}

	void update(int i, T x){
		for(; i <= size; i+=(i&(-i))){
			v[i]+=x;
		}
	}
};