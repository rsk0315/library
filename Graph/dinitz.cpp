/**
 * @brief 最大流 (Dinitz)
 * @author えびちゃん
 */

#ifndef H_max_flow_dinitz
#define H_max_flow_dinitz

#ifdef CALL_FROM_TEST
#include "utility/literals.cpp"
#include "utility/limits.cpp"
#include "utility/make/fix_point.cpp"
#include "Graph/adjacency_list.cpp"
#include "Graph/capacitated_list.cpp"
#endif

#include <queue>
#include <vector>

struct dinitz_tag {} dinitz;

template <typename AdjacencyList>
auto max_flow(AdjacencyList& g, size_t s, size_t t,
              typename AdjacencyList::weight_type fl, dinitz_tag) {

  using size_type = typename AdjacencyList::size_type;
  using weight_type = typename AdjacencyList::weight_type;
  size_type n = g.size();
  std::vector<size_type> level(n), iter(n);

  auto bfs = [&](size_type s) -> void {
    level.assign(n, -1_zu);
    std::queue<size_type> q;
    level[s] = 0;
    q.push(s);
    while (!q.empty()) {
      size_type v = q.front();
      q.pop();
      for (auto const& e: g[v]) {
        if (e.capacity() > weight_type(0) && level[e.target()] == -1_zu) {
          level[e.target()] = level[e.source()] + 1;
          q.push(e.target());
        }
      }
    }
  };

  auto dfs = make_fix_point([&](auto dfs_, size_type v, weight_type f) -> weight_type {
      if (v == t) return f;
      for (size_type& i = iter[v]; i < g[v].size(); ++i) {
        auto& e = g[v][i];
        if (e.capacity() > weight_type(0) && level[v] < level[e.target()]) {
          weight_type f0 = dfs_(e.target(), std::min(f, e.capacity()));
          if (f0 > weight_type(0)) {
            e.capacity() -= f0;
            g[e.target()][e.reversed()].capacity() += f0;
            return f0;
          }
        }
      }
      return weight_type(0);
  });

  weight_type res{0};
  while (true) {
    bfs(s);
    if (level[t] == -1_zu) return res;
    iter.assign(n, 0);
    weight_type f;
    while ((f = dfs(s, fl)) > weight_type(0)) {
      res += f;
      fl -= f;
      if (fl == weight_type(0)) return res;
    }
  }
}

template <typename AdjacencyList>
auto max_flow(AdjacencyList& g, size_t s, size_t t, dinitz_tag) {
  auto fl = limits<typename AdjacencyList::weight_type>::max();
  return max_flow(g, s, t, fl, dinitz);
}

#endif  /* !defined(H_max_flow_dinitz) */
