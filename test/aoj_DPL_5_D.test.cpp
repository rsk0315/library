#define PROBLEM "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DPL_5_D"

#include <cstdio>

#include "ModularArithmetic/modint.cpp"
#include "ModularArithmetic/modtable.cpp"

using mi = modint<1000'000'007>;

int main() {
  intmax_t n, k;
  scanf("%jd %jd", &n, &k);

  modtable<mi> mt(n+k);
  printf("%d\n", mt.binom(n+k-1, k-1).get());
}
