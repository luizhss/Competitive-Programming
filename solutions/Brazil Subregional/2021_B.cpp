/*
	Beautiful Words - 2020 LA Regional

	Prerequisites: RMQ data structure
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
 
const int MAX = 2e5+7, INF = 1e9+7;

const int ALPHA = 27;
struct SuffixAutomaton{
    int len[2*MAX], link[2*MAX], next[2*MAX][ALPHA];
    int sz, last;

    SuffixAutomaton() : sz(1), last(0) {
        len[0] = 0;
        link[0] = -1;
        memset(next[0], -1, sizeof next[0]);
    }

    int toi(char c) {
        if(c == '$') return 26;
        return c-'a';
    }

    void add(char c) {
        c = toi(c);
        int cur = sz++;
        len[cur] = len[last] + 1;
        memset(next[cur], -1, sizeof next[cur]);
        int p = last;
        while (p != -1 && next[p][c] == -1) {
            next[p][c] = cur; p = link[p];
        }
        if (p == -1) {
            link[cur] = 0;
        } else {
            int q = next[p][c];
            if (len[p] + 1 == len[q]) {
                link[cur] = q;
            } else {
                len[sz] = len[p] + 1;
                link[sz] = link[q];
                memcpy(next[sz], next[q], sizeof next[q]);
                while (p != -1 && next[p][c] == q) {
                    next[p][c] = sz; p = link[p];
                }
                link[q] = link[cur] = sz++;
            }
        }
        last = cur;
    }

    void lcs (string T, vi& dp) {
        int v = 0, l = 0;
        FOR(i, T.size()) {
            int c = toi(T[i]);
            while (v && next[v][c] == -1) {
                v = link[v];
                l = len[v];
            }
            if (next[v][c] != -1) {
                v = next[v][c];
                l++;
            }
            dp.PB(l);
        }
    } 
};
 
int main(){
	ios::sync_with_stdio(false); cin.tie(0);
 
	int n, m; cin >> n >> m;
	string s; cin >> s;
	s = s + s;
	string t = "";
	FOR(i, m){
		string x; cin >> x;
		t = t + "$" + x;
	}

    SuffixAutomaton sa;
    for(auto& c : t) sa.add(c);

    vi dp;
	sa.lcs(s, dp);

	int ans = 1e9;
	multiset<int> vis;
	int l = 2*n-1;
	for(int i = 2*n-1; i > n-1; i--){
		int lx = i-n+1;
        l = min(l, i);
		while(l >= lx && l-lx+1 >= dp[l]){
			vis.insert(dp[l--]);
		}

		int cur = l-lx+1;
		if(!vis.empty()){
			cur = max(cur, *prev(vis.end()));
		}
		ans = min(ans, cur);

		if(!vis.empty()){
			vis.erase(vis.find(dp[i]));
		}
	}

	cout << ans << '\n';
 
	return 0;
}