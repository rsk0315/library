#define PROBLEM "https://judge.yosupo.jp/problem/vertex_set_path_composite"

#include <cstdint>
#include <cstdio>
#include <utility>
#include <vector>

#include "Graph/hl_decomposition.cpp"
#include "DataStructure/basic_segment_tree.cpp"
#include "ModularArithmetic/modint.cpp"
#include "utility/monoid/composite.cpp"

constexpr intmax_t mod = 998244353;
using mi = modint<mod>;

int main() {
  size_t n, q;
  scanf("%zu %zu", &n, &q);

  std::vector<composite_monoid<mi>> f(n);
  for (auto& fi: f) {
    intmax_t a, b;
    scanf("%jd %jd", &a, &b);
    fi = {a, b};
  }

  std::vector<std::pair<size_t, size_t>> es;
  es.reserve(n-1);
  for (size_t i = 1; i < n; ++i) {
    size_t u, v;
    scanf("%zu %zu", &u, &v);
    es.emplace_back(u, v);
  }

  hl_decomposed_tree<basic_segment_tree<composite_monoid<mi>>, value_on_vertex_tag> g(f, es);
  for (size_t i = 0; i < q; ++i) {
    int t;
    scanf("%d", &t);

    if (t == 0) {
      size_t p;
      intmax_t c, d;
      scanf("%zu %jd %jd", &p, &c, &d);
      f[p] = {c, d};
      g.modify(p, f[p]);
    } else if (t == 1) {
      size_t u, v;
      intmax_t x;
      scanf("%zu %zu %jd", &u, &v, &x);
      printf("%jd\n", g.fold(u, v)(x).get());
    }
  }
}
