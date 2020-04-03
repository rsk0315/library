#define PROBLEM "https://judge.yosupo.jp/problem/scc"

#define CALL_FROM_TEST
#include "Graph/adjacency_list.cpp"
#include "Graph/scc.cpp"
#undef CALL_FROM_TEST

#include <cstddef>
#include <cstdio>
#include <algorithm>
#include <vector>

int main() {
  size_t n, m;
  scanf("%zu %zu", &n, &m);

  adjacency_list<weighted_edge<int>, directed_tag> g(n);
  for (size_t i = 0; i < m; ++i) {
    size_t u, v;
    scanf("%zu %zu", &u, &v);
    g.emplace(u, v, 1);
  }

  auto scc = strongly_connected_components(g);
  size_t k = *std::max_element(scc.begin(), scc.end()) + 1;

  std::vector<std::vector<size_t>> ts(k);
  for (size_t i = 0; i < n; ++i)
    ts[scc[i]].push_back(i);

  printf("%zu\n", k);
  for (size_t i = 0; i < k; ++i) {
    printf("%zu", ts[i].size());
    for (auto v: ts[i]) printf(" %zu", v);
    puts("");
  }
}
