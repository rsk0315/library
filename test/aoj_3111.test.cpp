#define PROBLEM "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=3111"

#include <cstdint>
#include <cstdio>
#include <algorithm>
#include <vector>

#include "utility/literals.cpp"
#include "utility/monoid/max_subsum.cpp"
#include "DataStructure/basic_segment_tree.cpp"

int main() {
  size_t n, q;
  scanf("%zu %zu", &n, &q);

  std::vector<intmax_t> a(n);
  for (auto& ai: a) scanf("%jd", &ai);

  basic_segment_tree<max_subsum_monoid<intmax_t>> st(a.begin(), a.end());
  printf("%jd\n", std::max(st.fold(0, n).get(), 0_jd));

  for (size_t i = 0; i < q; ++i) {
    size_t k;
    intmax_t x;
    scanf("%zu %jd", &k, &x);
    --k;
    st.set(k, x);
    printf("%jd\n", std::max(st.fold(0, n).get(), 0_jd));
  }
}
