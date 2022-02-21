/*
	Jumping Grasshoper - 2019 LA Regional

	Prerequisites: Seg Tree
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
 
const int MAX = 2e5+7;
const int INF = 0x3f3f3f3f;

struct Node{
    int maxi;
    Node(){
        maxi = -1;
    }
    Node(int val){
        maxi = val;
    }
};

Node merge(Node& a, Node& b){
    return Node(max(a.maxi, b.maxi));
}

struct SegTree{
    int size;
    std::vector<Node> seg;

    SegTree(int n): size(n){
        seg.resize(4*size);
    }

    void build(std::vector<int>& v){
        build(0, 0, size-1, v);
    }

    void build(int pos, int lx, int rx, std::vector<int>& v){
        if(lx == rx){
            seg[pos] = Node(v[lx]);
            return;
        }

        int q = (lx+rx)/2;
        build(2*pos+1, lx, q, v);
        build(2*pos+2, q+1, rx, v);
        seg[pos] = merge(seg[2*pos+1], seg[2*pos+2]);
    }

    Node query(int l, int r){
        return query(0, 0, size-1, l, r);
    }

    Node query(int pos, int lx, int rx, int l, int r){
        if(l > rx || r < lx) return Node();
        if(l <= lx && rx <= r) return seg[pos];

        int q = (lx+rx)/2;
        Node p1 = query(2*pos+1, lx, q, l, r);
        Node p2 = query(2*pos+2, q+1, rx, l, r);
        return merge(p1, p2);
    }

    void update(int idx, int x){
        update(0, 0, size-1, idx, x);
    }

    void update(int pos, int lx, int rx, int idx, int x){
        if(idx < lx || idx > rx) return;
        if(lx == rx){
            seg[pos] = Node(x);
            return;
        }
        int q = (lx + rx)/2;
        update(2*pos+1, lx, q, idx, x);
        update(2*pos+2, q+1, rx, idx, x);
        seg[pos] = merge(seg[2*pos+1], seg[2*pos+2]);
    }

    int bb(int l, int r, int h, bool right=false){
    	return bb(0, 0, size-1, l, r, h, right);
    }

    int bb(int pos, int lx, int rx, int l, int r, int h, bool right=false){
		if(seg[pos].maxi < h) return (right ? -INF : INF);
		if(r < lx || rx < l) return (right ? -INF : INF);
		if(lx == rx){
			if(seg[pos].maxi > h) return lx;
			return (right ? -INF : INF);
		}
		int q = (lx+rx)>>1;
		if(lx <= l && r <= rx){
			if(right){
				if(seg[2*pos+2].maxi > h)
					return bb(2*pos+2, q+1, rx, l, r, h, right);
				if(seg[2*pos+1].maxi > h)
					return bb(2*pos+1, lx, q, l, r, h, right);
			}else{
				if(seg[2*pos+1].maxi > h)
					return bb(2*pos+1, lx, q, l, r, h, right);
				if(seg[2*pos+2].maxi > h)
					return bb(2*pos+2, q+1, rx, l, r, h, right);
			}
			return (right ? -INF : INF);
		}
		
		int p1 = bb(2*pos+1, lx, q, l, r, h, right);
		int p2 = bb(2*pos+2, q+1, rx, l, r, h, right);
		return (right ? max(p1, p2) : min(p1, p2));
	} 
};
 
int main(){
	ios::sync_with_stdio(false); cin.tie(0);
 
	int n, m; cin >> n >> m;
	vi v(n); FOR(i, n) cin >> v[i];
 
	SegTree seg(n);
	seg.build(v);
 
	int idx;
	FOR(i, m){
		char c; cin >> c >> idx;
		--idx;
		if(c == 'U'){
			int h; cin >> h;
			seg.update(idx, h);
			v[idx] = h;
		}else{

			int l, r; l = r = -1;
			if(idx > 0)
				l = seg.query(0, idx-1).maxi;
			if(idx+1 < n)
				r = seg.query(idx+1, n-1).maxi;
			     
			if(l == -1 || l < v[idx]){
				if(c == 'L') cout << idx+1 << '\n';
				else{
					int ret = seg.bb(idx+1, n-1, v[idx]);
					if(ret == INF) cout << idx+1 << '\n';
					else cout << ret+1 << '\n';
				}
			}else if(r == -1 || r < v[idx]){
				if(c == 'R') cout << idx+1 << '\n';
				else{
					int ret = seg.bb(0, idx-1, v[idx], true);
					if(ret == -INF) cout << idx+1 << '\n';
					else cout << ret+1 << '\n';
				}
			}else{
				if(l < r){
					int ret = seg.bb(idx+1, n-1, l);
					if(ret == INF) cout << idx+1 << '\n';
					else cout << ret+1 << '\n';
				}else{
					int ret = seg.bb(0, idx-1, r, true);
					if(ret == -INF) cout << idx+1 << '\n';
					else cout << ret+1 << '\n';
				}
			}
		}
	}
 
	return 0;
}