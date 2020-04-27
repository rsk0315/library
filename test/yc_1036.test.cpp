#define PROBLEM "https://yukicoder.me/problems/no/1036"

#include <cstdint>
#include <cstdio>
#include <algorithm>
#include <numeric>
#include <vector>

#include "DataStructure/foldable_queue.cpp"
#include "utility/monoid/gcd.cpp"

int main() {
  size_t n;
  scanf("%zu", &n);

  std::vector<intmax_t> a(n);
  for (auto& ai: a) scanf("%jd", &ai);

  foldable_queue<gcd_monoid<intmax_t>> q;
  intmax_t res = n*(n+1)/2;
  for (size_t il = 0, ir = 0; il < n; ++il) {
    while (ir < n && (q.fold() + a[ir]).get() != 1) {
      q.push(a[ir++]);
    }
    res -= ir-il;
    if (ir == il) ++ir; else q.pop();
  }

  printf("%jd\n", res);
}
