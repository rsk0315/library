#define PROBLEM "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DPL_5_G"

#include <cstdint>
#include <cstdio>

#include "ModularArithmetic/modint.cpp"
#include "ModularArithmetic/modtable.cpp"
#include "ModularArithmetic/operations.cpp"

using mi = modint<1000'000'007>;

int main() {
  intmax_t n, k;
  scanf("%jd %jd", &n, &k);

  modtable<mi> mt(n+k);
  mi res = 0;
  for (int j = 1; j <= k; ++j) {
    mi res0 = 0;
    for (int i = 1; i <= j; ++i) {
      mi cur = mt.binom(j, i);
      if ((i-1) % 2) cur = -cur;
      cur *= pow(mi(j-i), n);
      res0 += cur;
    }
    res0 = (pow(mi(j), n) - res0) * mt.factorial_inverse(j);
    res += res0;
  }
  printf("%jd\n", res.get());
}
