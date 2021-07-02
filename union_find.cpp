// https://atcoder.jp/contests/abl/submissions/23858399
// https://atcoder.jp/contests/abc177/submissions/23858440

#include <vector>

struct union_find {
private :
    std::vector<int> v;
    int root_counter;
public :
    union_find(int n) : v(n, -1), root_counter(n) { }
    int root(int k) { return (v[k] < 0 ? k : v[k] = root(v[k])); }
    bool is_united(int i, int j) { return root(i) == root(j); }
    bool unite(int i, int j) {
        i = root(i); j = root(j);
        if (i == j) return false;
        if (v[i] > v[j]) std::swap(i, j);
        v[i] += v[j];
        v[j] = i;
        root_counter--;
        return true;
    }
    int count_root() const { return root_counter; }
    int size(int k) { return -v[root(k)]; }
};