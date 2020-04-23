#define IGNORE
// @ignore

#include <cstdio>

#include "integer/fused_multiply.cpp"

int main() {
  int w = fused_mul_mod(1000000, 1000000, 998244353);
  printf("%d\n", w);
}
