int xor128() {
    static int x = 123456789, y = 362436069, z = 521288629, w = 88675123;
    int t;
    t = (x ^ (x << 11));
    x = y;
    y = z;
    z = w;
    return (w = (w ^ (w >> 19)) ^ (t ^ (t >> 8)));
}

struct Node {
    int val;
    Node *ch[2];
    // 優先度
    int pri;
    // 部分木の個数
    int cnt;
    // 部分木の値の和
    int s;
    Node(int val, int p) : val(val), pri(p), cnt(1), s(val) {
        ch[0] = ch[1] = nullptr;
    }
};
int count(Node *n) { return n == nullptr ? 0 : n->cnt; }
int sum(Node *n) { return n == nullptr ? 0 : n->s; }

Node *update(Node *n) {
    n->cnt = count(n->ch[0]) + count(n->ch[1]) + 1;
    n->s = sum(n->ch[0]) + sum(n->ch[1]) + n->val;
    return n;
}

Node *merge(Node *l, Node *r) {
    if (l == nullptr || r == nullptr) return l == nullptr ? r : l;
    if (l->pri > r->pri) {
        l->ch[1] = merge(l->ch[1], r);
        return update(l);
    } else {
        r->ch[0] = merge(l, r->ch[0]);
        return update(r);
    }
}

pair<Node *, Node *> split(Node *t, int k) {
    if (t == nullptr) return make_pair(nullptr, nullptr);
    int c = count(t->ch[0]);
    if (k <= c) {
        auto s = split(t->ch[0], k);
        t->ch[0] = s.second;
        return make_pair(s.first, update(t));
    } else {
        auto s = split(t->ch[1], k - c - 1);
        t->ch[1] = s.first;
        return make_pair(update(t), s.second);
    }
}

Node *insert(Node *t, int k, int val) {
    Node *m = new Node(val, xor128() % 1007);
    auto p = split(t, k);
    return merge(merge(p.first, m), p.second);
}

Node *erase(Node *t, int k) {
    auto p1 = split(t, k);
    auto p2 = split(p1.second, 1);
    return merge(p1.first, p2.second);
}

// valを挿入するべき場所を探す
int upper_bound(Node *t, int val) {
    if (t == nullptr) return 0;
    if (t->val > val)
        return upper_bound(t->ch[0], val);
    else
        return upper_bound(t->ch[1], val) + count(t->ch[0]) + 1;
}

// x番目の大きいやつ
int get(Node *t, int x) {
    int c = count(t->ch[0]);
    if (c == x) return t->val;
    if (x < c)
        return get(t->ch[0], x);
    else
        return get(t->ch[1], x - c - 1);
}
