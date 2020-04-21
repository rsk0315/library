#define IGNORE
// @ignore

#include <cstdint>
#include <cstdio>

#include "ModularArithmetic/modint.cpp"

constexpr intmax_t mod = 998244353;
using mi = modint<mod>;

int main() {
  printf("%jd\n", (mi(2) - 3).get());
  printf("%jd\n", (2 - mi(3)).get());
  printf("%jd\n", (mi(1) / 2).get());
  printf("%jd\n", (1 / mi(2)).get());
}
