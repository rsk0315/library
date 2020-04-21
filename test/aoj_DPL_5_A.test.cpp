#define PROBLEM "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DPL_5_A"

#include <cstdio>

#include "ModularArithmetic/modint.cpp"
#include "ModularArithmetic/operations.cpp"

using mi = modint<1000'000'007>;

int main() {
  intmax_t n, k;
  scanf("%jd %jd", &n, &k);
  printf("%d\n", pow(mi(k), n).get());
}
