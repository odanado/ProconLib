struct UnionFind {
    int size_;
    vector<int> par;
    vector<int> rank;
    vector<int> sz;

    UnionFind(int size_) : size_(size_) {
        par.resize(size_);
        rank.resize(size_);
        sz.resize(size_);

        for (int i = 0; i < size_; i++) {
            par[i] = i;
            rank[i] = 0;
            sz[i] = 1;
        }
    }

    int find(int x) { return par[x] == x ? x : par[x] = find(par[x]); }
    void unite(int x, int y) {
        x = find(x);
        y = find(y);
        if (x == y) return;

        if (rank[y] < rank[x]) swap(x, y);
        if (rank[x] == rank[y]) rank[x]++;

        par[x] = y;
        sz[y] += sz[x];
    }
    bool same(int x, int y) { return find(x) == find(y); }
    int size(int x) { return sz[find(x)]; }
};
