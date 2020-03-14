#define PROBLEM "https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=0575"

#define CALL_FROM_TEST
#include "algorithm/parallel_binary_search.cpp"
#include "DataStructure/union_find.cpp"
#include "Graph/adjacency_list.cpp"
#include "utility/limits.cpp"
#undef CALL_FROM_TEST

#include <cstdio>
#include <cstdint>
#include <algorithm>
#include <functional>
#include <map>
#include <queue>
#include <vector>

class spred {
  disjoint_set M_ds;
  std::vector<std::vector<std::pair<size_t, size_t>>> M_es;
  size_t M_st;

public:
  spred() = default;
  spred(size_t n, std::vector<std::vector<std::pair<size_t, size_t>>> const& es):
    M_ds(n), M_es(es), M_st(es.size()) {}

  void next() {
    for (auto const& e: M_es[--M_st]) M_ds.unite(e.first, e.second);
  }

  bool operator ()(std::pair<size_t, size_t> const& e) {
    return !M_ds.equivalent(e.first, e.second);
  }

  size_t size() const { return M_es.size(); }
};

template <typename Tp>
using greater_priority_queue = std::priority_queue<Tp, std::vector<Tp>, std::greater<>>;

int main() {
  size_t n, m, k, q;
  scanf("%zu %zu %zu %zu", &n, &m, &k, &q);

  adjacency_list<weighted_edge<int>, undirected_tag> g(n);
  for (size_t i = 0; i < m; ++i) {
    size_t u, v;
    int w;
    scanf("%zu %zu %d", &u, &v, &w);
    --u, --v;
    g.emplace(u, v, w);
  }

  std::vector<size_t> f(k);
  for (auto& fi: f) scanf("%zu", &fi), --fi;

  std::vector<int> dist(n, limits<int>::max());
  greater_priority_queue<std::pair<int, size_t>> pq;
  for (auto fi: f) {
    dist[fi] = 0;
    pq.emplace(0, fi);
  }

  while (!pq.empty()) {
    auto [w, v] = pq.top();
    pq.pop();
    if (w > dist[v]) continue;
    for (auto const& e: g[v]) {
      size_t nv = e.target();
      int nw = dist[v] + e.weight();
      if (dist[nv] > nw) {
        dist[nv] = nw;
        pq.emplace(nw, nv);
      }
    }
  }

  std::map<int, size_t> enc;
  std::vector<int> dec;
  for (auto d: dist) enc[d];
  {
    size_t i = 0;
    for (auto& p: enc) {
      p.second = i++;
      dec.push_back(p.first);
    }
  }

  std::vector<std::vector<std::pair<size_t, size_t>>> es(dec.size());
  for (size_t i = 0; i < n; ++i) {
    for (auto const& e: g[i]) {
      size_t u = e.source();
      size_t v = e.target();
      if (dist[u] + e.weight() <= dist[v]) {
        es[enc.at(dist[u])].emplace_back(u, v);
      }
      if (dist[u] <= dist[v]) {
        es[enc.at(dist[u])].emplace_back(u, v);
      }
    }
  }

  std::vector<std::pair<size_t, size_t>> st(q);
  for (auto& p: st) scanf("%zu %zu", &p.first, &p.second), --p.first, --p.second;

  auto res = parallel_binary_search(spred(n, es), st.begin(), st.end());
  for (auto ri: res) printf("%d\n", dec[es.size()-ri]);
}
