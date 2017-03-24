template <typename T>
inline size_t hashCombine(size_t seed, const T& v) {
    return seed ^ (hash<T>()(v) + 0x9e3779b9 + (seed << 6) + (seed >> 2));
}
namespace std {
template <typename... Ts>
class hash<tuple<Ts...>> {
 public:
    size_t operator()(const tuple<Ts...>& t) const { return impl<0>(t); }

 private:
    template <size_t Index>
    typename enable_if<Index == tuple_size<tuple<Ts...>>::value, size_t>::type
    impl(const tuple<Ts...>&) const {
        return 0;
    }
    template <size_t Index>
    typename enable_if<Index != tuple_size<tuple<Ts...>>::value, size_t>::type
    impl(const tuple<Ts...>& t) const {
        return hashCombine(impl<Index + 1>(t), get<Index>(t));
    }
};
}
