#define PROBLEM "https://judge.yosupo.jp/problem/lca"

#define CALL_FROM_TEST
#include "Graph/adjacency_list.cpp"
#include "Graph/lowest_common_ancestor_squaring.cpp"
#undef CALL_FROM_TEST

#include <cstddef>
#include <cstdio>

int main() {
  size_t n, q;
  scanf("%zu %zu", &n, &q);

  adjacency_list<weighted_edge<int>, undirected_tag> g(n);
  for (size_t i = 1; i < n; ++i) {
    size_t p;
    scanf("%zu", &p);
    g.emplace(i, p, 1);
  }

  lowest_common_ancestor lca(g, 0);
  for (size_t i = 0; i < q; ++i) {
    size_t u, v;
    scanf("%zu %zu", &u, &v);
    printf("%zu\n", lca(u, v));
  }
}
