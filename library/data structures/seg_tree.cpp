/*
	Segment Tree (Vanilla version)
	
	Efficiently update and calculates query on a range.
	This implementation is zero-based indexing.

	Operations:
		query(l, r) -> query for f in range [l, r]
		update(i, x) -> updates i-th element to x
	
	Complexity:
		(constructor) -> O(n)
		query() -> O(log(n))
		update() -> O(log(n))
*/

struct Node{
    int x;
    Node(){
        x = 0;
    }
    Node(int val){
        x = val;
    }
};

struct SegTree{
    int size;
    std::vector<Node> seg;

    SegTree(int n): size(n){
        seg.resize(4*size);
    }

    Node merge(Node& a, Node& b){
        return Node(a.x+b.x);
    }

    void build(std::vector<long long>& v){
        build(0, 0, size-1, v);
    }

    void build(int pos, int lx, int rx, std::vector<long long>& v){
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
        if(l > rx || r < lx)
            return Node();
        if(l <= lx && rx <= r)
            return seg[pos];

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
};