#define PROBLEM "https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_5_C"

#include <cstdint>
#include <cstdio>
#include <vector>

#include "utility/stack_extend.cpp"
#include "Graph/adjacency_list.cpp"
#include "Graph/lowest_common_ancestor_sparse_table.cpp"

int main() {
  BEGIN_STACK_EXTEND(128*1024*1024);

  int n;
  scanf("%d", &n);

  adjacency_list<weighted_edge<int>, undirected_tag> g(n);
  for (size_t i = 0; i < n; ++i) {
    size_t k;
    scanf("%zu", &k);
    for (size_t j = 0; j < k; ++j) {
      size_t c;
      scanf("%zu", &c);
      g.emplace(i, c, 1);
    }
  }

  lowest_common_ancestor g_lca(g, 0);

  size_t q;
  scanf("%zu", &q);
  for (size_t i = 0; i < q; ++i) {
    size_t u, v;
    scanf("%zu %zu", &u, &v);
    printf("%zu\n", g_lca(u, v));
  }

  END_STACK_EXTEND;
}
