// https://atcoder.jp/contests/jsc2021/submissions/23902075

#include <functional>
#include <memory>

template<typename T, typename index_type> struct dynamic_segment_tree {
    using F = std::function<T(T, T)>;
    struct node {
        T val;
        index_type l, r;
        std::unique_ptr<node> children[2];
        node(const T& val_, index_type l_, index_type r_) : val(val_), l(l_), r(r_) { }
        void make_children() {
            if (!children[0]) {
                children[0] = std::make_unique<node>(val, l, (l + r) / 2);
                children[1] = std::make_unique<node>(val, (l + r) / 2, r);
            }
        }
    };
private :
    const F f;
    const T e;
    std::unique_ptr<node> root;

    void update(index_type k, const T& x, node& now) {
        if (now.l + 1 == now.r) {
            now.val = x;
            return;
        }
        now.make_children();
        update(k, x, *now.children[k >= (now.l + now.r) / 2]);
        now.val = f(now.children[0]->val, now.children[1]->val);
    }
    T fold(index_type l, index_type r, const node& now) const {
        if (now.r <= l || r <= now.l) return e;
        if (l <= now.l && now.r <= r) return now.val;
        T ret = e;
        if (now.children[0]) ret = f(ret, fold(l, r, *now.children[0]));
        if (now.children[1]) ret = f(ret, fold(l, r, *now.children[1]));
        return ret;
    }
public :
    dynamic_segment_tree(const F& f_, const T& e_) : f(f_), e(e_) { }
    void build(index_type l, index_type r) { root = std::make_unique<node>(e, l, r); }
    void update(index_type k, const T& x) { update(k, x, *root); }
    T fold(index_type l, index_type r) const { return fold(l, r, *root); }
};