#define PROBLEM "https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=2976"

#define CALL_FROM_TEST
#include "Graph/dinitz.cpp"
#include "DataStructure/union_find.cpp"
#undef CALL_FROM_TEST

#include <cstdio>
#include <utility>
#include <vector>

int main() {
  size_t n, m;
  scanf("%zu %zu", &n, &m);

  adjacency_list<capacitated_edge<int>, directed_tag> g(n+n+2);
  size_t source = n+n;
  size_t sink = source+1;

  for (size_t i = 0; i < n; ++i) {
    g.emplace(source, i, 1);
    g.emplace(n+i, sink, 1);
  }

  std::vector<std::pair<size_t, size_t>> rs(m);
  for (size_t i = 0; i < m; ++i) {
    size_t x, y;
    scanf("%zu %zu", &x, &y);
    --x, --y;
    rs[i] = std::make_pair(x, y);
    g.emplace(x, n+y, 1);
  }

  disjoint_set ds(m);
  int min = m - max_flow(g, source, sink, dinitz);
  int max = 0;

  for (size_t i = 0; i < m; ++i)
    for (size_t j = 0; j < i; ++j)
      if (rs[i].first == rs[j].first || rs[i].second == rs[j].second)
        if (ds.unite(i, j)) ++max;

  printf("%d %d\n", min, max);
}
