// https://judge.yosupo.jp/submission/52215

#include <vector>
#include <queue>
#include <algorithm>

struct DIJKSTRA {
    using G = std::vector<std::vector<std::pair<long long, int>>>; // {weight, end of a edge}
private :
    std::vector<long long> dist;
    std::vector<int> path;
public :
    const std::vector<long long>& operator()(const G& g, int start) {
        int n = g.size();
        dist.resize(n, -1);
        path.resize(n, -1);
        using P = std::pair<long long, std::pair<int, int>>; // {distance, {from, to}}
        std::priority_queue<P, std::vector<P>, std::greater<P>> pq;
        pq.push({0, {-1, start}});
        while (!pq.empty()) {
            auto [d, edge] = pq.top(); pq.pop();
            if (dist[edge.second] != -1) continue;
            dist[edge.second] = d;
            path[edge.second] = edge.first;
            for (auto [weight, next] : g[edge.second]) {
                if (dist[next] == -1) pq.push({d + weight, {edge.second, next}});
            }
        }
        return dist;
    }
    std::vector<int> restore(int last_node) const {
        std::vector<int> ret;
        do { ret.emplace_back(last_node); } while ((last_node = path[last_node]) != -1);
        std::reverse(ret.begin(), ret.end());
        return ret;
    }
}; DIJKSTRA dijkstra;