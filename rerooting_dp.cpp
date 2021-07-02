// https://atcoder.jp/contests/abc160/submissions/23918930?lang=ja

#include <vector>
#include <functional>

template<typename T> struct rerooting_dp {
    using F = std::function<T(T, T)>;
    using G = std::function<T(T)>;
    struct edge {
        T val;
        long long weight;
        int to, reversed_idx;
        edge(const T& val_, long long weight_, int to_, int reversed_idx_)
            : val(val_), weight(weight_), to(to_), reversed_idx(reversed_idx_) { }
    };
private :
    const int N;
    const F f;
    const G g;
    const T e;
    std::vector<std::vector<edge>> graph;
    std::vector<T> dp;
    std::vector<std::vector<T>> lsum, rsum;

    T dfs1(int prev, int now) {
        T ret = e;
        for (auto& next : graph[now]) {
            if (next.to != prev) ret = f(ret, next.val = dfs1(now, next.to));
        }
        return g(ret);
    }
    void build_sum(int k) {
        int m = graph[k].size();
        lsum[k].resize(m + 1, e); rsum[k].resize(m + 1, e);
        for (int i = 0; i < m; i++) {
            lsum[k][i + 1] = f(lsum[k][i], graph[k][i].val);
            rsum[k][m - 1 - i] = f(graph[k][m - 1 - i].val, rsum[k][m - i]);
        }
    }
    void dfs2(int prev, int now, int idx) {
        if (prev != -1) {
            if (lsum[prev].size() == 0) build_sum(prev);
            int reversed_idx = graph[prev][idx].reversed_idx;
            graph[now][reversed_idx].val = g(f(lsum[prev][idx], rsum[prev][idx + 1]));
        }
        for (unsigned i = 0; i < graph[now].size(); i++) {
            if (graph[now][i].to != prev) dfs2(now, graph[now][i].to, i);
        }
    }
public :
    rerooting_dp(int N_, const F& f_, const G& g_, const T& e_) : N(N_), f(f_), g(g_), e(e_) {
        graph.resize(N);
        dp.resize(N, e);
        lsum.resize(N);
        rsum.resize(N);
    }
    void add_edge(int u, int v, long long weight = 1) {
        graph[u].emplace_back(e, weight, v, graph[v].size());
        graph[v].emplace_back(e, weight, u, graph[u].size() - 1);
    }
    const std::vector<T>& calculate() {
        dfs1(-1, 0);
        dfs2(-1, 0, -1);
        for (int i = 0; i < N; i++) {
            if (lsum[i].size() == 0) build_sum(i);
            dp[i] = g(lsum[i].back());
        }
        return dp;
    }
};