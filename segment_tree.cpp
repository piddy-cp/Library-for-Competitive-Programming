// https://atcoder.jp/contests/abc194/submissions/23868022
// https://atcoder.jp/contests/arc033/submissions/23868530
// https://atcoder.jp/contests/code-festival-2014-qualb/submissions/23868526

#include <vector>
#include <functional>

template<typename T> struct segment_tree {
    using F = std::function<T(T, T)>;
private :
    const F f;
    const T e;
    int W = 1;
    std::vector<T> v;
public :
    segment_tree(const F& f_, const T& e_) : f(f_), e(e_) { }
    template<typename RandomAccessIterator>
    void build(RandomAccessIterator first, RandomAccessIterator last) {
        while (W < last - first) W <<= 1;
        v.resize(W << 1, e);
        for (int i = 0; i < last - first; i++) v[i + W] = *(first + i);
        for (int i = W - 1; i > 0; i--) v[i] = f(v[i << 1], v[(i << 1) + 1]);
    }
    void update(int k, const T& x) {
        v[k += W] = x;
        while (k >>= 1) v[k] = f(v[k << 1], v[(k << 1) + 1]);
    }
    T fold(int l, int r) const {
        T ret_l = e, ret_r = e;
        l += W; r += W;
        while (l < r) {
            if (l & 1) ret_l = f(ret_l, v[l++]);
            if (r & 1) ret_r = f(v[--r], ret_r);
            l >>= 1; r >>= 1;
        }
        return f(ret_l, ret_r);
    }
    const T& get(int k) const { return v[k + W]; }
    int binary_search(int l, int r, const std::function<bool(T)>& ok) const {
        T folded = e;
        int k = l + W, length = 1;
        while (!ok(f(folded, v[k])) && l + length < W) {
            if (k & 1) {
                folded = f(folded, v[k++]);
                l += length;
            }
            k >>= 1;
            length <<= 1;
        }
        if (!ok(f(folded, v[k]))) return r;
        while (k < W) {
            T tmp = f(folded, v[k <<= 1]);
            if (!ok(tmp)) {
                folded = tmp;
                k++;
            }
        }
        return std::min(k - W, r);
    }
};