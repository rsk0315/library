#define PROBLEM "https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DPL_5_B"

#define CALL_FROM_TEST
#include "ModularArithmetic/modint.cpp"
#undef CALL_FROM_TEST

using mi = modint<1000'000'007>;

#include <cstdio>

int main() {
  intmax_t n, k;
  scanf("%jd %jd", &n, &k);

  if (n > k) return puts("0"), 0;

  mi res = 1;
  for (int i = 0; i < n; ++i) res *= k-i;
  printf("%jd\n", res.get());
}
