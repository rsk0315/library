#define PROBLEM "https://judge.yosupo.jp/problem/point_set_range_composite"

#include <cstdint>
#include <cstdio>
#include <vector>

#include "DataStructure/basic_segment_tree.cpp"
#include "utility/monoid/composite.cpp"
#include "ModularArithmetic/modint.cpp"

constexpr intmax_t mod = 998244353;
using mi = modint<mod>;

int main() {
  size_t n, q;
  scanf("%zu %zu", &n, &q);

  std::vector<composite_monoid<mi>> f(n);
  for (size_t i = 0; i < n; ++i) {
    int a, b;
    scanf("%d %d", &a, &b);
    f[i] = {a, b};
  }

  basic_segment_tree<composite_monoid<mi>> st(f.begin(), f.end());
  for (size_t i = 0; i < q; ++i) {
    int t;
    scanf("%d", &t);

    if (t == 0) {
      size_t p;
      int c, d;
      scanf("%zu %d %d", &p, &c, &d);
      st.set(p, {c, d});
    } else if (t == 1) {
      size_t l, r;
      intmax_t x;
      scanf("%zu %zu %jd", &l, &r, &x);
      printf("%d\n", st.fold(l, r)(x).get());
    }
  }
}
