/*
    Segment Tree (Lazy Propagation)
    
    Efficiently update and calculates query on a range.
    This implementation is zero-based indexing.

    Operations:
        query(l, r) -> query for f in range [l, r]
        update(l, r, x) -> updates the range [l, r] by x
    
    Complexity:
        query() -> O(log(n))
        update() -> O(log(n))
*/

struct Node{
    int x, lazy;
    Node(){
        x = lazy = 0;
    }
    Node(int val){
        x = val;
        lazy = 0;
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

    void push(int pos, int lx, int rx){
        if(seg[pos].lazy == 0) return;
        auto lazy = seg[pos].lazy;
        seg[pos].lazy = 0;
        seg[pos].x += (rx-lx+1) * lazy;
        if(lx != rx){
            seg[2*pos+1].lazy += lazy;
            seg[2*pos+2].lazy += lazy;
        } 
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
        push(pos, lx, rx);

        if(r < lx || l > rx) return Node();
        if(l <= lx && rx <= r) return seg[pos];

        int q = (lx+rx)/2;
        Node p1 = query(2*pos+1, lx, q, l, r);
        Node p2 = query(2*pos+2, q+1, rx, l, r);
        return merge(p1, p2);
    }

    void update(int l, int r, int x){
        update(0, 0, size-1, l, r, x);
    }

    void update(int pos, int lx, int rx, int l, int r, int x){
        push(pos, lx, rx);
        if(r < lx || l > rx) return;
        if(l <= lx && rx <= r){ // update lazy
            seg[pos].lazy += x;
            push(pos, lx, rx);
            return;
        }

        int q = (lx + rx)/2;
        update(2*pos+1, lx, q, l, r, x);
        update(2*pos+2, q+1, rx, l, r, x);
        seg[pos] = merge(seg[2*pos+1], seg[2*pos+2]);
    }
};