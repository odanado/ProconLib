template <typename T>
inline size_t hash_combine(size_t seed, const T& v) {
    return seed ^ (hash<T>()(v) + 0x9e3779b9 + (seed << 6) + (seed >> 2));
}

namespace std {
template <typename T, typename S>
class hash<pair<T, S>> {
 public:
    size_t operator()(const pair<T, S>& p) const {
        size_t seed = 0;
        seed = hash_combine(seed, p.first);
        seed = hash_combine(seed, p.second);
        return seed;
    }
};
}
