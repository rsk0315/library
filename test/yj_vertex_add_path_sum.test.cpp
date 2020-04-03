#define PROBLEM "https://judge.yosupo.jp/problem/vertex_add_path_sum"

#define CALL_FROM_TEST
#include "Graph/hl_decomposition.cpp"
#include "DataStructure/basic_segment_tree.cpp"
#undef CALL_FROM_TEST

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <utility>
#include <vector>

int main() {
  size_t n, q;
  scanf("%zu %zu", &n, &q);

  std::vector<intmax_t> a(n);
  for (auto& ai: a) scanf("%jd", &ai);

  std::vector<std::pair<size_t, size_t>> es;
  es.reserve(n-1);
  for (size_t i = 1; i < n; ++i) {
    size_t u, v;
    scanf("%zu %zu", &u, &v);
    es.emplace_back(u, v);
  }

  hl_decomposed_tree<basic_segment_tree<intmax_t>, value_on_vertex_tag> g(a, es);
  for (size_t i = 0; i < q; ++i) {
    int t;
    scanf("%d", &t);

    if (t == 0) {
      size_t p;
      intmax_t x;
      scanf("%zu %jd", &p, &x);
      a[p] += x;
      g.modify(p, a[p]);
    } else if (t == 1) {
      size_t u, v;
      scanf("%zu %zu", &u, &v);
      printf("%jd\n", g.fold(u, v));
    }
  }
}
