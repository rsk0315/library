/**
 * @brief 強連結成分分解
 * @author えびちゃん
 */

#ifndef H_strongly_connected_components
#define H_strongly_connected_components

#ifdef CALL_FROM_TEST
#include "utility/make/fix_point.cpp"
#include "Graph/adjacency_list.cpp"
#endif

#include <cstddef>
#include <vector>

template <typename AdjacencyList>
auto strongly_connected_components(AdjacencyList const& g) {
  size_t n = g.size();
  adjacency_list<weighted_edge<bool>, directed_tag> h(n);
  for (size_t v = 0; v < n; ++v)
    for (auto const& e: g[v]) h.emplace(e.target(), e.source(), 1);

  std::vector<bool> used(n);
  std::vector<size_t> vs;
  auto dfs = make_fix_point([&](auto f, size_t v) -> void {
      used[v] = true;
      for (auto const& e: g[v])
        if (!used[e.target()]) f(e.target());
      vs.push_back(v);
  });
  for (size_t v = 0; v < n; ++v)
    if (!used[v]) dfs(v);

  used.assign(n, false);
  std::vector<size_t> cmp(n);
  size_t num = 0;
  auto rdfs = make_fix_point([&](auto f, size_t v) -> void {
      used[v] = true;
      cmp[v] = num;
      for (auto const& e: h[v])
        if (!used[e.target()]) f(e.target());
  });
  for (size_t v = vs.size(); v--;)
    if (!used[vs[v]])
      rdfs(vs[v]), ++num;

  return cmp;
}

#endif /* !defined(H_strongly_connected_components) */
