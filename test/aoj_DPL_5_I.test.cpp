#define PROBLEM "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DPL_5_I"

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
  for (int i = 1; i <= k; ++i) {
    mi cur = mt.binom(k, i);
    if ((i-1) % 2) cur = -cur;
    cur *= pow(mi(k-i), n);
    res += cur;
  }
  res = (pow(mi(k), n) - res) * mt.factorial_inverse(k);
  printf("%d\n", res.get());
}
