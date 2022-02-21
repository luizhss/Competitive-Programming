/*
    Job Allocator - 2020 LA Regional
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
typedef unsigned int u_int;
typedef vector<int> vi;
typedef pair<int,int> pii;
 
const int MAX = 1e5+7;
 
int res[8], aux[8];
unordered_map<u_int, int> dp;
 
u_int convertToNum(){
	u_int ret = 0;
	for(int i = 0; i < 8; i++){
		ret |= (aux[i]<<(4*i));
	}
	return ret;
}
 
void add(){
	for(int i1 = res[0]; i1 >= 0; i1--){
	for(int i2 = res[1]; i2 >= 0; i2--){
	for(int i3 = res[2]; i3 >= 0; i3--){
	for(int i4 = res[3]; i4 >= 0; i4--){
	for(int i5 = res[4]; i5 >= 0; i5--){
	for(int i6 = res[5]; i6 >= 0; i6--){
	for(int i7 = res[6]; i7 >= 0; i7--){
	for(int i8 = res[7]; i8 >= 0; i8--){
	
		aux[0] = i1;
		aux[1] = i2;
		aux[2] = i3;
		aux[3] = i4;
		aux[4] = i5;
		aux[5] = i6;
		aux[6] = i7;
		aux[7] = i8;
 
		u_int val = convertToNum();
		dp[val]++;
 
	}}}}}}}}
}
 
void erase(){
	for(int i1 = res[0]; i1 >= 0; i1--){
	for(int i2 = res[1]; i2 >= 0; i2--){
	for(int i3 = res[2]; i3 >= 0; i3--){
	for(int i4 = res[3]; i4 >= 0; i4--){
	for(int i5 = res[4]; i5 >= 0; i5--){
	for(int i6 = res[5]; i6 >= 0; i6--){
	for(int i7 = res[6]; i7 >= 0; i7--){
	for(int i8 = res[7]; i8 >= 0; i8--){
	
		aux[0] = i1;
		aux[1] = i2;
		aux[2] = i3;
		aux[3] = i4;
		aux[4] = i5;
		aux[5] = i6;
		aux[6] = i7;
		aux[7] = i8;
 
		u_int val = convertToNum();
		dp[val]--;
 
	}}}}}}}}
}
 
int main(){
	ios::sync_with_stdio(false); cin.tie(0);
 
	vector<u_int> vis;
 
	int n, k; cin >> n >> k;
	FOR(i, n){
		char type; cin >> type;
		u_int val;
		memset(res, 0, sizeof res);
 
		if(type == 'C'){
			int t; cin >> t;
			FOR(j, t){
				int x; cin >> x;
				res[x-1]++;
			}
			FOR(j, 8) aux[j] = res[j];
 
			vis.PB(convertToNum());
			add();
 
		}else if(type == 'J'){
			int t; cin >> t;
			FOR(j, t){
				int x; cin >> x;
				res[x-1]++;
			}
			FOR(j, 8) aux[j] = res[j];
 
			val = convertToNum();
 
			if(dp.count(val)){
				cout << dp[val] << '\n';
			}else{
				cout << "0\n";
			}
 
		}else{
			int x; cin >> x;
			val = vis[x-1];
			FOR(j, 8){
				res[j] = (val & 0xF);
				val >>= 4;
			}
 
			erase();
		}
	}
 
	return 0;
}