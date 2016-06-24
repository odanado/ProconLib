struct SCC {
    vector<vector<int>> adj;
    vector<vector<int>> rev;
    vector<int> vs;
    vector<int> cmp;
    vector<bool> used;
    int V;
    SCC(int n) : V(n) {
        adj.resize(n);
        rev.resize(n);
        cmp.resize(n);
        used.resize(n);
    }

    void addEdge(int to, int from) {
        adj[to].push_back(from);
        rev[from].push_back(to);
    }
    void dfs(int v) {
        used[v] = true;
        for (auto u : adj[v]) {
            if (!used[u]) dfs(u);
        }
        vs.push_back(v);
    }
    void rdfs(int v, int k) {
        used[v] = true;
        cmp[v] = k;
        for (auto u : rev[v]) {
            if (!used[u]) rdfs(u, k);
        }
    }

    int operator()() {
        used.assign(V, 0);
        vs.clear();
        rep(i, V) if (!used[i]) dfs(i);
        used.assign(V, 0);

        int k = 0;
        for (int i = vs.size() - 1; i >= 0; i--) {
            if (!used[vs[i]]) rdfs(vs[i], k++);
        }
        return k;
    }
    bool same(int v, int u) { return cmp[v] == cmp[u]; }
};
