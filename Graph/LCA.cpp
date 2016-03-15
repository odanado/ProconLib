// Verified http://abc014.contest.atcoder.jp/tasks/abc014_4
struct LCA {
    int N;
    int root;
    int log2_n;
    vector<vector<int>> parent;
    vector<int> depth;
    vector<vector<int>> G;
    LCA(int N,int root=0) : N(N), root(root) {
        log2_n = log2(N) + 1;
        parent.resize(log2_n);
        rep(i,log2_n) parent[i].resize(N);
        depth.resize(N);
        G.resize(N);
    }
    void add_edge(int v,int u) {
        G[v].pb(u);
    }
    void init() {
        dfs(root,-1,0);
        rep(k,log2_n-1) rep(v,N) {
            if(parent[k][v]<0) parent[k+1][v]=-1;
            else parent[k+1][v]=parent[k][parent[k][v]];
        }
    }
    void dfs(int v,int p,int d) {
        parent[0][v]=p;
        depth[v]=d;
        rep(i,G[v].size()) {
            if(G[v][i]!=p) dfs(G[v][i],v,d+1);
        }
    }
    int operator()(int u,int v) {
        if(depth[u]>depth[v]) swap(u,v);
        rep(k,log2_n) {
            if((depth[v]-depth[u])>>k&1) {
                v=parent[k][v];
            }
        }
        if(v==u) return u;

        for(int k=log2_n-1;k>=0;k--) {
            if(parent[k][u]!=parent[k][v]) {
                u=parent[k][u];
                v=parent[k][v];
            }
        }
        return parent[0][u];
    }
    int dist(int v,int u) {
        int a=operator()(v,u);
        return depth[v] - depth[a] + depth[u] - depth[a];
    }
};

