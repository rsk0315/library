#ifndef H_shortest_path
#define H_shortest_path

/**
 * @brief グラフ上の最短距離
 * @author えびちゃん
 */

#include <deque>
#include <functional>
#include <queue>
#include <utility>
#include <vector>

#include "utility/limits.cpp"

struct dijkstra_tag {} dijkstra;
struct bfs01_tag {} bfs01;

template <typename AdjacencyList>
auto shortest_path(AdjacencyList const& g, size_t s, dijkstra_tag) {
  size_t n = g.size();
  using weight_type = typename AdjacencyList::weight_type;
  using pair = std::pair<weight_type, size_t>;
  std::vector<weight_type> d(n, limits<weight_type>::max());
  d[s] = 0;
  std::priority_queue<pair, std::vector<pair>, std::greater<>> pq;
  pq.emplace(0, s);
  while (!pq.empty()) {
    weight_type w;
    size_t v;
    std::tie(w, v) = pq.top();
    pq.pop();
    if (d[v] < w) continue;
    for (auto const& e: g[v]) {
      size_t nv = e.target();
      auto nw = w + e.weight();
      if (nw < d[nv]) {
        d[nv] = nw;
        pq.emplace(nw, nv);
      }
    }
  }
  return d;
}

template <typename AdjacencyList>
auto shortest_path(AdjacencyList const& g, size_t s, bfs01_tag) {
  size_t n = g.size();
  std::vector<size_t> d(n, n);
  d[s] = 0;
  std::deque<size_t> dq;
  dq.push_back(s);
  while (!dq.empty()) {
    size_t v = dq.front();
    dq.pop_front();
    for (auto const& e: g[v]) {
      size_t nv = e.target();
      size_t nw = d[v] + ((e.weight() == 0)? 0: 1);
      if (!(nw < d[nv])) continue;
      d[nv] = nw;
      if (e.weight() == 0) {
        dq.push_front(nv);
      } else {
        dq.push_back(nv);
      }
    }
  }
  return d;
}

#endif  /* !defined(H_shortest_path) */
