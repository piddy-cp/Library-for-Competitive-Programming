// https://judge.yosupo.jp/submission/51912
// https://atcoder.jp/contests/abl/submissions/23885889

#include <vector>
#include <functional>

template<typename T, typename U> struct lazy_segment_tree {
    using F = std::function<T(T, T, int, int, int)>;
    using G = std::function<T(T, U, int, int)>;
    using H = std::function<U(U, U)>;
private :
    const F f;
    const G g;
    const H h;
    const T e1;
    const U e2;
    int W = 1;
    std::vector<std::pair<int, int>> segment;
    std::vector<T> v;
    std::vector<U> w;

    void propagate(int k) {
        if (w[k] == e2) return;
        auto [a, b] = segment[k];
        v[k] = g(v[k], w[k], a, b);
        if (k < W) {
            w[k << 1] = h(w[k << 1], w[k]);
            w[(k << 1) + 1] = h(w[(k << 1) + 1], w[k]);
        }
        w[k] = e2;
    }
public :
    lazy_segment_tree(F f_, G g_, H h_, T e1_, U e2_) : f(f_), g(g_), h(h_), e1(e1_), e2(e2_) { }
    template<typename RandomAccessIterator>
    void build(RandomAccessIterator first, RandomAccessIterator last) {
        while (W < last - first) W <<= 1;
        segment.resize(W << 1);
        v.resize(W << 1, e1);
        w.resize(W << 1, e2);
        for (int i = 0; i < W; i++) segment[i + W] = {i, i + 1};
        for (int i = 0; i < last - first; i++) v[i + W] = *(first + i);
        for (int i = W - 1; i > 0; i--) {
            auto [a, b] = segment[i] = {segment[i << 1].first, segment[(i << 1) + 1].second};
            v[i] = f(v[i << 1], v[(i << 1) + 1], a, (a + b) / 2, b);
        }
    }
    void update(int l, int r, const U& x, int k = 1) {
        auto [a, b] = segment[k];
        if (l <= a && b <= r) {
            w[k] = h(w[k], x);
            propagate(k);
            return;
        }
        propagate(k);
        if (b <= l || r <= a) return;
        update(l, r, x, k << 1);
        update(l, r, x, (k << 1) + 1);
        v[k] = f(v[k << 1], v[(k << 1) + 1], a, (a + b) / 2, b);
    }
    T fold(int l, int r, int k = 1) {
        auto [a, b] = segment[k];
        if (b <= l || r <= a) return e1;
        propagate(k);
        if (l <= a && b <= r) return v[k];
        int m = (a + b) / 2;
        a = std::max(a, l);
        b = std::min(b, r);
        (m = std::max(m, a)) = std::min(m, b);
        return f(fold(l, r, k << 1), fold(l, r, (k << 1) + 1), a, m, b);
    }
};