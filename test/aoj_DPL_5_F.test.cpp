#define PROBLEM "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DPL_5_F"

#include <cstdint>
#include <cstdio>

#include "ModularArithmetic/modint.cpp"
#include "ModularArithmetic/modtable.cpp"

using mi = modint<1000'000'007>;

int main() {
  intmax_t n, k;
  scanf("%jd %jd", &n, &k);

  modtable<mi> mt(n);
  printf("%d\n", mt.binom(n-1, k-1).get());
}
