#define PROBLEM "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DPL_5_B"

#include <cstdint>
#include <cstdio>

#include "ModularArithmetic/modint.cpp"

using mi = modint<1000'000'007>;

int main() {
  intmax_t n, k;
  scanf("%jd %jd", &n, &k);

  if (n > k) return puts("0"), 0;

  mi res = 1;
  for (int i = 0; i < n; ++i) res *= k-i;
  printf("%d\n", res.get());
}
