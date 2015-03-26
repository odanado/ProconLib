/*
 * 最大流
 * Ford Fulkerson法
 * O(F|E|)
 *
 * http://poj.org/problem?id=3281
 *
 */

struct FordFulkerson{
    struct Edge { 
        int to,cap,rev; 
        Edge(int to=0,int cap=0,int rev=0) :
            to(to),cap(cap),rev(rev){}
    };

    int V;
    vector<vector<Edge> > G;
    vector<bool> used;

    FordFulkerson(int V) : V(V) {
        G.resize(V);
        used.assign(V,false);
    }

    void add_edge(int from,int to,int cap) {
        G[from].pb(Edge(to,cap,G[to].size()));
        G[to].pb(Edge(from,0,G[from].size()-1));
    }

    int dfs(int v,int t,int f) {
        if(v==t) return f;
        used[v]=true;
        for(int i=0;i<G[v].size();i++) {
            Edge &e=G[v][i];

            if(!used[e.to] && e.cap>0) {
                int d=dfs(e.to,t,min(f,e.cap));
                if(d>0) {
                    e.cap-=d;
                    G[e.to][e.rev].cap+=d;
                    return d;
                }
            }
        }
        return 0;
    }

    int max_flow(int s,int t) {
        int flow=0;
        while(1) {
            used.assign(V,false);
            int f=dfs(s,t,INF);
            if(f==0) break;
            flow+=f;
        }

        return flow;
    }
};
