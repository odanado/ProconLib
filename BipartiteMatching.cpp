/*
 * 二部マッチング
 * O(|E||V|)
 *
 * http://poj.org/problem?id=3041
 */

struct BipartiteMatching {
    vector<vector<int> > G;
    vector<int> match;
    vector<bool> used;

    int V;
    BipartiteMatching(int V):V(V){
        G.resize(V);
        match.resize(V);
        used.resize(V);
    }

    void add_edge(int u,int v) {
        G[u].push_back(v);
        G[v].push_back(u);
    }

    bool dfs(int v) {
        used[v]=true;
        for(int i=0;i<G[v].size();i++){
            int u=G[v][i];
            int w=match[u];
            if(w<0||!used[w]&&dfs(w)) {
                match[v]=u;
                match[u]=v;
                return true;
            }
        }
        return false;
    }

    int operator() () {
        int res=0;
        match.assign(V,-1);
        for(int v=0;v<V;v++){
            if(match[v]<0) {
                used.assign(V,0);
                if(dfs(v)) res++;
            }
        }
        return res;
    }
};
