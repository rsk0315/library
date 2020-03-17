#define PROBLEM "https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DPL_5_D"

#define CALL_FROM_TEST
#include "ModularArithmetic/modint.cpp"
#include "ModularArithmetic/modtable.cpp"
#undef CALL_FROM_TEST

using mi = modint<1000'000'007>;

#include <cstdio>

int main() {
  intmax_t n, k;
  scanf("%jd %jd", &n, &k);

  modtable<mi> mt(n+k);
  printf("%jd\n", mt.binom(n+k-1, k-1).get());
}
