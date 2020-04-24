#define PROBLEM "https://judge.yosupo.jp/problem/bipartitematching"

#include <cstdio>
#include <vector>

#include "Graph/capacitated_adjacency_list.cpp"
#include "Graph/dinitz.cpp"

int main() {
  size_t l, r, m;
  scanf("%zu %zu %zu", &l, &r, &m);

  adjacency_list<capacitated_edge<int>, directed_tag> g(l+r+2);
  size_t source = l+r;
  size_t sink = source+1;
  for (size_t i = 0; i < m; ++i) {
    size_t a, b;
    scanf("%zu %zu", &a, &b);
    g.emplace(a, l+b, 1);
  }

  for (size_t i = 0; i < l; ++i) g.emplace(source, i, 1);
  for (size_t i = 0; i < r; ++i) g.emplace(l+i, sink, 1);

  printf("%d\n", max_flow(g, source, sink, dinitz));

  for (size_t i = 0; i < l; ++i) {
    for (auto const& e: g[i]) {
      size_t j = e.target();
      if (j == source) continue;
      if (e.capacity() == 0) printf("%zu %zu\n", i, j-l);
    }
  }
}
