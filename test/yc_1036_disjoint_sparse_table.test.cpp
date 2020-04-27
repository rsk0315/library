#define PROBLEM "https://yukicoder.me/problems/no/1036"

#include <cstdint>
#include <cstdio>
#include <algorithm>
#include <vector>

#include "DataStructure/disjoint_sparse_table.cpp"
#include "utility/monoid/gcd.cpp"

int main() {
  size_t n;
  scanf("%zu", &n);

  std::vector<intmax_t> a(n);
  for (auto& ai: a) scanf("%jd", &ai);

  disjoint_sparse_table<gcd_monoid<intmax_t>> st(a.begin(), a.end());

  intmax_t res = 0;
  for (size_t i = 0; i < n; ++i) {
    if (st.fold(i, n).get() > 1) break;
    size_t lb = i, ub = n;
    while (ub-lb > 1) {
      size_t mid = (lb+ub) / 2;
      ((st.fold(i, mid).get() > 1)? lb: ub) = mid;
    }
    res += n-lb;
  }

  printf("%jd\n", res);
}
