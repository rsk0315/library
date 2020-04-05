#define PROBLEM "https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_5_D"

#include <cstdio>
#include <cassert>
#include <tuple>
#include <vector>

#include "DataStructure/basic_segment_tree.cpp"
#include "Graph/hl_decomposition.cpp"

int main() {
  size_t n;
  scanf("%zu", &n);

  std::vector<size_t> par(n, n);
  std::vector<std::tuple<size_t, size_t, int>> es;
  for (size_t i = 0; i < n; ++i) {
    size_t k;
    scanf("%zu", &k);
    for (size_t j = 0; j < k; ++j) {
      size_t c;
      scanf("%zu", &c);
      par[c] = i;
      es.emplace_back(i, c, 0);
    }
  }

  hl_decomposed_tree<basic_segment_tree<int>, value_on_undirected_edge_tag> g(n, es);

  size_t q;
  scanf("%zu", &q);

  for (size_t i = 0; i < q; ++i) {
    int t;
    scanf("%d", &t);

    if (t == 0) {
      size_t v;
      int w;
      scanf("%zu %d", &v, &w);
      w += g.fold(v, par[v]);
      g.modify(v, w);
    } else if (t == 1) {
      size_t u;
      scanf("%zu", &u);
      int res = g.fold(u, 0);
      assert(res == g.fold(0, u));
      printf("%d\n", res);
    }
  }
}
