#define PROBLEM "https://judge.yosupo.jp/problem/range_affine_range_sum"

#include <cstdint>
#include <cstdio>
#include <vector>

#include "DataStructure/segment_tree.cpp"
#include "utility/action/affine_sum.cpp"
#include "ModularArithmetic/modint.cpp"

constexpr intmax_t mod = 998244353;
using mi = modint<mod>;

int main() {
  size_t n, q;
  scanf("%zu %zu", &n, &q);

  std::vector<intmax_t> a(n);
  for (auto& ai: a) scanf("%jd", &ai);

  segment_tree<action_affine_to_sum<mi>> st(a.begin(), a.end());

  for (size_t i = 0; i < q; ++i) {
    int t;
    scanf("%d", &t);

    if (t == 0) {
      size_t l, r;
      intmax_t b, c;
      scanf("%zu %zu %jd %jd", &l, &r, &b, &c);
      st.act(l, r, {b, c});
    } else if (t == 1) {
      size_t l, r;
      scanf("%zu %zu", &l, &r);
      printf("%jd\n", st.fold(l, r).get().get());
    }
  }
}
