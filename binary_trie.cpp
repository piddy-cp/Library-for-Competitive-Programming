// https://judge.yosupo.jp/submission/52161
// https://atcoder.jp/contests/arc033/submissions/23901716

#include <memory>
#include <cassert>

template<int B> struct binary_trie {
    using ull = unsigned long long;
    struct node {
        ull cnt = 0;
        std::unique_ptr<node> children[2];
        void make_children(bool bit) {
            if (!children[bit]) children[bit] = std::make_unique<node>();
        }
    };
private :
    std::unique_ptr<node> root;
    void insert(ull n, ull x, node& now, ull i) {
        now.cnt += x;
        if (i == 0) return;
        now.make_children(n & i);
        insert(n, x, *now.children[!!(n & i)], i >> 1);
    }
    void erase(ull n, ull x, node& now, ull i) {
        assert(now.cnt >= x); now.cnt -= x;
        if (i == 0) return;
        erase(n, x, *now.children[!!(n & i)], i >> 1);
    }
    ull count(ull n, const node& now, ull i) const {
        if (i == 0) return now.cnt;
        return (now.children[!!(n & i)] ? count(n, *now.children[!!(n & i)], i >> 1) : 0);
    }
    ull xor_min(ull n, const node& now, ull i) const {
        if (i == 0) return 0;
        bool bit = n & i, exist = now.children[bit] && now.children[bit]->cnt;
        return xor_min(n, *now.children[!(bit ^ exist)], i >> 1) | (!(bit ^ exist) ? i : 0);
    }
    ull kth_element(ull n, const node& now, ull i) const {
        if (i == 0) return 0;
        ull cnt = (now.children[0] ? now.children[0]->cnt : 0);
        return kth_element(n > cnt ? n - cnt : n, *now.children[n > cnt], i >> 1) | (n > cnt ? i : 0);
    }
public :
    binary_trie() : root(std::make_unique<node>()) { }
    void insert(ull n, ull x = 1) { insert(n, x, *root, 1ULL << (B - 1)); }
    void erase(ull n, ull x = 1) { if (x == 0) return; erase(n, x, *root, 1ULL << (B - 1)); }
    ull count(ull n) const { return count(n, *root, 1ULL << (B - 1)); }
    ull xor_min(ull n) const { assert(root->cnt > 0); return xor_min(n, *root, 1ULL << (B - 1)); }
    ull kth_element(ull n) const { return kth_element(n, *root, 1ULL << (B - 1)); }
};