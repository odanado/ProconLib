using Weight = ll;
struct Edge {
    int to;
    Weight cost;
};
struct Node {
    int v;
    Node(int v) : v(v) {}
    bool operator<(const Node &rhs) const { return tie(v) < tie(rhs.v); }
    bool operator==(const Node &rhs) const { return tie(v) == tie(rhs.v); }
};

namespace std {
template <>
struct hash<Node>{
    size_t operator()(const Node &node) const {
        size_t seed = 0;

        size_t v_hash = hash<int>()(node.v);

        seed ^= v_hash + 0x9e3779b9 + (seed << 6) + (seed >> 2);
        return seed;
    }
};
}
struct State : public Node {
    Weight cost;
    State(Node node, Weight cost) : Node(node), cost(cost) {}
    bool operator<(const State &rhs) const { return cost > rhs.cost; }
};

unordered_map<Node, Weight> dijkstra(const vector<vector<Edge>> &adj,
                           const Node &source) {
    unordered_map<Node, Weight> dist;
    priority_queue<State> que;

    que.push(State(source, 0));
    dist[source] = 0;

    while (que.size()) {
        State s = que.top();
        que.pop();
        Node cur{s.v};

        for (auto u : adj[s.v]) {
            Node next{u.to};
            if (!dist.count(next) || dist[next] > dist[cur] + u.cost) {
                dist[next] = dist[cur] + u.cost;
                que.push(State(next, dist[next]));
            }
        }
    }

    return dist;
}

