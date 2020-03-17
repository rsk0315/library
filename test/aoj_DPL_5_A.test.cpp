#define PROBLEM "https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DPL_5_A"

#define CALL_FROM_TEST
#include "ModularArithmetic/modint.cpp"
#include "ModularArithmetic/operations.cpp"
#undef CALL_FROM_TEST

using mi = modint<1000'000'007>;

#include <cstdio>

int main() {
  intmax_t n, k;
  scanf("%jd %jd", &n, &k);
  printf("%jd\n", pow(mi(k), n).get());
}
