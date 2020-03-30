/**
 * @brief トポロジカルソート
 * @author えびちゃん
 */

#ifndef H_topological_sort
#define H_topological_sort

#include <queue>
#include <vector>

template <typename AdjacencyList>
std::vector<size_t> topological_sort(AdjacencyList const& g) {
  size_t n = g.size();
  std::vector<size_t> ord, indeg(n, 0);
  std::queue<size_t> q;
  ord.reserve(n);
  for (size_t v = 0; v < n; ++v)
    for (auto const& e: g[v]) ++indeg[e.target()];
  for (size_t v = 0; v < n; ++v)
    if (indeg[v] == 0) q.push(v);
  while (!q.empty()) {
    size_t v = q.front();
    q.pop();
    ord.push_back(v);
    for (auto const& e: g[v]) {
      size_t u = e.target();
      if (--indeg[u] == 0) q.push(u);
    }
  }
  if (ord.size() < n) ord.clear();
  return ord;
}

#endif  /* !defined(H_topological_sort) */
