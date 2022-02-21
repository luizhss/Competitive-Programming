/*
    Kruskal algorithm (Minimum Spanning Tree)
    
    Given a graph and the weight of each edge. Find
    the minimum spanning tree of the graph.

    Complexity:
        kruskal() -> O(ElogV)

    Requires:
        DSU
*/

struct Edge{
    int u, v, w;
    bool operator<(const Edge& other) const{
        return w < other.w;
    }
};

std::vector<Edge> kruskal(std::vector<Edge> edges, int& cost, int n){
    std::vector<Edge> result;
    initialize(n);
    std::sort(edges.begin(), edges.end());
    cost = 0;
    for(auto& [u, v, w] : edges){
        if(find(u) != find(v)){
            join(u, v);
            cost += w;
            result.push_back({u, v, w});
        }
    }
    return result;
}